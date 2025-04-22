#pragma once

#include "runtime/function/render/render_scene.h"
#include "runtime/function/render/render_swap_context.h"
#include "runtime/function/render/render_type.h"

#include <memory>
#include <string>
#include <unordered_map>

namespace Toon
{
    class RHI;
    class RenderScene;
    class RenderCamera;

    struct GlobalRenderResource
    {
        //TODO
    };

    class RenderResource
    {
    public:
        RenderResource() {}
        ~RenderResource() {}

        void clear();

        void uploadGlobalRenderResource(std::shared_ptr<RHI> rhi, LevelResourceDesc level_resource_desc);

        void uploadGameObjectRenderResource(std::shared_ptr<RHI> rhi,
            RenderEntity         render_entity,
            RenderMeshData       mesh_data,
            RenderMaterialData   material_data);

        void uploadGameObjectRenderResource(std::shared_ptr<RHI> rhi,
            RenderEntity         render_entity,
            RenderMeshData       mesh_data);

        void uploadGameObjectRenderResource(std::shared_ptr<RHI> rhi,
            RenderEntity         render_entity,
            RenderMaterialData   material_data);

        void updatePerFrameBuffer(std::shared_ptr<RenderScene>  render_scene,
            std::shared_ptr<RenderCamera> camera);

        OpenGLMesh& getEntityMesh(RenderEntity entity);

        OpenGLMaterial& getEntityMaterial(RenderEntity entity);
        // TODO: data caching
        RenderMeshData               loadMeshData(const MeshSourceDesc& source, AxisAlignedBox& bounding_box);
        RenderMaterialData           loadMaterialData(const MaterialSourceDesc& source);
        AxisAlignedBox               getCachedBoudingBox(const MeshSourceDesc& source) const;

    public:
        // global rendering resource
        GlobalRenderResource m_global_render_resource;
        // storage buffer objects
        MeshPerframeStorageBufferObject                         m_mesh_perframe_storage_buffer_object;
        MeshPointLightShadowPerframeStorageBufferObject         m_mesh_point_light_shadow_perframe_storage_buffer_object;
        MeshDirectionalLightShadowPerframeStorageBufferObject   m_mesh_directional_light_shadow_perframe_storage_buffer_object;
        // cached mesh and material
        std::map<size_t, OpenGLMesh>        m_opengl_meshes;
        std::map<size_t, OpenGLMaterial>    m_opengl_pbr_materials;
    private:
        StaticMeshData loadStaticMesh(std::string mesh_file, AxisAlignedBox& bounding_box);
        OpenGLMesh& getOrCreateOpenGLMesh(std::shared_ptr<RHI> rhi, RenderEntity entity, RenderMeshData mesh_data);
        OpenGLMaterial& getOrCreateOpenGLMaterial(std::shared_ptr<RHI> rhi, RenderEntity entity, RenderMaterialData material_data);
        void updateMeshData(std::shared_ptr<RHI>                          rhi,
            uint32_t                                        index_buffer_size,
            void*                                           index_buffer_data,
            uint32_t                                        vertex_buffer_size,
            MeshVertexDataDefinition *                      vertex_buffer_data,
            OpenGLMesh& now_mesh);
    private:
        std::unordered_map<MeshSourceDesc, AxisAlignedBox> m_bounding_box_cache_map;
    };
} // namespace Toon
