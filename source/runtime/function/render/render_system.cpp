#include "runtime/core/base/macro.h"
#include "runtime/core/base/error.h"
#include "runtime/resource/config_manager.h"
#include "runtime/resource/asset_manager.h"
#include "runtime/function/global/global_context.h"
#include "runtime/function/render/render_camera.h"
#include "runtime/function/render/render_system.h"
#include "runtime/function/render/window_system.h"
#include "runtime/function/render/render_pipeline.h"
#include "runtime/function/render/render_resource.h"
#include "runtime/function/render/render_scene.h"
#include "runtime/function/render/opengl/opengl_rhi.h"
#include "runtime/function/render/opengl/opengl_shader.h"
#include "runtime/function/render/debugdraw/debug_draw_manager.h"
#include "runtime/resource/res_type/global/global_rendering.h"

namespace Toon
{
	RenderSystem::~RenderSystem()
	{
		clear();
	}
	void RenderSystem::initialize(RenderSystemInitInfo init_info)
	{
		LOG_INFO("RenderSystem initialize");

		std::shared_ptr<ConfigManager> config_manager = g_runtime_global_context.m_config_manager;
		ASSERT(config_manager);
		std::shared_ptr<AssetManager> asset_manager = g_runtime_global_context.m_asset_manager;
		ASSERT(asset_manager);

		window_system = init_info.window_system;
		ASSERT(window_system);
		window_system->registerOnWindowSizeFunc(std::bind(&RenderSystem::onWindowSize,
			this,
			std::placeholders::_1,
			std::placeholders::_2));

		// render context initialize
		RHIInitInfo rhi_init_info;
		rhi_init_info.window_system = init_info.window_system;
		m_rhi = std::make_shared<OpenGLRHI>();
		m_rhi->Initialize(rhi_init_info);

		// global rendering resource
		GlobalRenderingRes global_rendering_res;
		const std::string& global_rendering_res_url = config_manager->getGlobalRenderingResUrl();
		asset_manager->loadAsset(global_rendering_res_url, global_rendering_res);
		
        // upload ibl, color grading textures
        LevelResourceDesc level_resource_desc;
        level_resource_desc.m_ibl_resource_desc.m_skybox_irradiance_map = global_rendering_res.m_skybox_irradiance_map;
        level_resource_desc.m_ibl_resource_desc.m_skybox_specular_map = global_rendering_res.m_skybox_specular_map;
        level_resource_desc.m_ibl_resource_desc.m_brdf_map = global_rendering_res.m_brdf_map;
        level_resource_desc.m_color_grading_resource_desc.m_color_grading_map =
            global_rendering_res.m_color_grading_map;

        m_render_resource = std::make_shared<RenderResource>();
        m_render_resource->uploadGlobalRenderResource(m_rhi, level_resource_desc);

        // setup render camera
        const CameraPose& camera_pose = global_rendering_res.m_camera_config.m_pose;
        m_render_camera = std::make_shared<RenderCamera>();
        m_render_camera->lookAt(camera_pose.m_position, camera_pose.m_target, camera_pose.m_up);
        m_render_camera->m_zfar = global_rendering_res.m_camera_config.m_z_far;
        m_render_camera->m_znear = global_rendering_res.m_camera_config.m_z_near;
        m_render_camera->setAspect(global_rendering_res.m_camera_config.m_aspect.x /
            global_rendering_res.m_camera_config.m_aspect.y);

        // setup render scene
        m_render_scene = std::make_shared<RenderScene>();
        m_render_scene->m_ambient_light = { global_rendering_res.m_ambient_light.toVector3() };
        m_render_scene->m_directional_light.m_direction = global_rendering_res.m_directional_light.m_direction.normalisedCopy();
        m_render_scene->m_directional_light.m_color = global_rendering_res.m_directional_light.m_color.toVector3();
        m_render_scene->setVisibleNodesReference();

        // initialize render pipeline
        RenderPipelineInitInfo pipeline_init_info;
        pipeline_init_info.enable_fxaa = global_rendering_res.m_enable_fxaa;
        pipeline_init_info.render_resource = m_render_resource;

        m_render_pipeline = std::make_shared<RenderPipeline>();
        m_render_pipeline->m_rhi = m_rhi;
        m_render_pipeline->initialize(pipeline_init_info);
	}

	void RenderSystem::tick(float delta_time)
	{
		processSwapData();
        m_render_pipeline->forwardRender(m_rhi, m_render_resource);
		//g_runtime_global_context.m_debugdraw_manager->tick(delta_time);
	}

	void RenderSystem::clear()
	{
		g_runtime_global_context.m_debugdraw_manager->clear();
	}


	void RenderSystem::onWindowSize(int width, int height)
	{
		m_rhi->SetViewPort(width, height);
	}

	void RenderSystem::swapLogicRenderData()
	{
		m_swap_context.swapLogicRenderData();
	}

	RenderSwapContext& RenderSystem::getSwapContext()
	{
		return m_swap_context;
	}

	std::shared_ptr<RenderCamera> RenderSystem::getRenderCamera() const 
	{ 
		return m_render_camera; 
	}

	std::shared_ptr<RHI> RenderSystem::getRHI() const
	{
		return m_rhi;
	}

	void RenderSystem::initializeUIRenderBackend(WindowUI* window_ui)
	{
		m_render_pipeline->initializeUIRenderBackend(window_ui);
	}

	void RenderSystem::processSwapData()
	{
        RenderSwapData& swap_data = m_swap_context.getRenderSwapData();

        std::shared_ptr<AssetManager> asset_manager = g_runtime_global_context.m_asset_manager;
        ASSERT(asset_manager);

        // TODO: update global resources if needed
        if (swap_data.m_level_resource_desc.has_value())
        {
            m_render_resource->uploadGlobalRenderResource(m_rhi, *swap_data.m_level_resource_desc);

            // reset level resource swap data to a clean state
            m_swap_context.resetLevelRsourceSwapData();
        }

        // update game object if needed
        if (swap_data.m_game_object_resource_desc.has_value())
        {
            while (!swap_data.m_game_object_resource_desc->isEmpty())
            {
                GameObjectDesc gobject = swap_data.m_game_object_resource_desc->getNextProcessObject();

                for (size_t part_index = 0; part_index < gobject.getObjectParts().size(); part_index++)
                {
                    const auto& game_object_part = gobject.getObjectParts()[part_index];
                    GameObjectPartId part_id = { gobject.getId(), part_index };

                    bool is_entity_in_scene = m_render_scene->getInstanceIdAllocator().hasElement(part_id);

                    RenderEntity render_entity;
                    render_entity.m_instance_id =
                        static_cast<uint32_t>(m_render_scene->getInstanceIdAllocator().allocGuid(part_id));
                    render_entity.m_model_matrix = game_object_part.m_transform_desc.m_transform_matrix;

                    m_render_scene->addInstanceIdToMap(render_entity.m_instance_id, gobject.getId());

                    // mesh properties
                    MeshSourceDesc mesh_source = { game_object_part.m_mesh_desc.m_mesh_file };
                    bool           is_mesh_loaded = m_render_scene->getMeshAssetIdAllocator().hasElement(mesh_source);

                    RenderMeshData mesh_data;
                    if (!is_mesh_loaded)
                    {
                        mesh_data = m_render_resource->loadMeshData(mesh_source, render_entity.m_bounding_box);
                    }
                    else
                    {
                        render_entity.m_bounding_box = m_render_resource->getCachedBoudingBox(mesh_source);
                    }

                    render_entity.m_mesh_asset_id = m_render_scene->getMeshAssetIdAllocator().allocGuid(mesh_source);                  

                    // material properties
                    MaterialSourceDesc material_source;
                    if (game_object_part.m_material_desc.m_with_texture)
                    {
                        material_source = { game_object_part.m_material_desc.m_base_color_texture_file,
                                           game_object_part.m_material_desc.m_metallic_roughness_texture_file,
                                           game_object_part.m_material_desc.m_normal_texture_file,
                                           game_object_part.m_material_desc.m_occlusion_texture_file,
                                           game_object_part.m_material_desc.m_emissive_texture_file };
                    }
                    else
                    {
                        // TODO: move to default material definition json file
                        material_source = {
                            asset_manager->getFullPath("asset/texture/default/albedo.jpg").generic_string(),
                            asset_manager->getFullPath("asset/texture/default/mr.jpg").generic_string(),
                            asset_manager->getFullPath("asset/texture/default/normal.jpg").generic_string(),
                            "",
                            "" };
                    }
                    bool is_material_loaded = m_render_scene->getMaterialAssetdAllocator().hasElement(material_source);

                    RenderMaterialData material_data;
                    if (!is_material_loaded)
                    {
                        material_data = m_render_resource->loadMaterialData(material_source);
                    }

                    render_entity.m_material_asset_id =
                        m_render_scene->getMaterialAssetdAllocator().allocGuid(material_source);

                    // create game object on the graphics api side
                    if (!is_mesh_loaded)
                    {
                        m_render_resource->uploadGameObjectRenderResource(m_rhi, render_entity, mesh_data);
                    }

                    if (!is_material_loaded)
                    {
                        m_render_resource->uploadGameObjectRenderResource(m_rhi, render_entity, material_data);
                    }

                    // add object to render scene if needed
                    if (!is_entity_in_scene)
                    {
                        m_render_scene->m_render_entities.push_back(render_entity);
                    }
                    else
                    {
                        for (auto& entity : m_render_scene->m_render_entities)
                        {
                            if (entity.m_instance_id == render_entity.m_instance_id)
                            {
                                entity = render_entity;
                                break;
                            }
                        }
                    }
                }
                // after finished processing, pop this game object
                swap_data.m_game_object_resource_desc->pop();
            }

            // reset game object swap data to a clean state
            m_swap_context.resetGameObjectResourceSwapData();
        }

        // remove deleted objects
        if (swap_data.m_game_object_to_delete.has_value())
        {
            while (!swap_data.m_game_object_to_delete->isEmpty())
            {
                GameObjectDesc gobject = swap_data.m_game_object_to_delete->getNextProcessObject();
                m_render_scene->deleteEntityByGObjectID(gobject.getId());
                swap_data.m_game_object_to_delete->pop();
            }

            m_swap_context.resetGameObjectToDelete();
        }

        // process camera swap data
        if (swap_data.m_camera_swap_data.has_value())
        {
            if (swap_data.m_camera_swap_data->m_fov_x.has_value())
            {
                m_render_camera->setFOVx(*swap_data.m_camera_swap_data->m_fov_x);
            }

            if (swap_data.m_camera_swap_data->m_view_matrix.has_value())
            {
                m_render_camera->setMainViewMatrix(*swap_data.m_camera_swap_data->m_view_matrix);
            }
            m_swap_context.resetCameraSwapData();
        }    
	}

}

