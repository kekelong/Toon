#include "runtime/function/render/render_pipeline.h"
#include "runtime/function/render/debugdraw/debug_draw_manager.h"
#include "runtime/core/base/macro.h"
#include "runtime/function/global/global_context.h"
#include "runtime/function/render/passes/ui_pass.h"
#include "runtime/function/render/passes/main_camera_pass.h"

namespace Toon
{
    void RenderPipeline::initialize(RenderPipelineInitInfo init_info)
    {
        UIPassInitInfo ui_init_info;
        m_ui_pass = std::make_shared<UIPass>();
        m_ui_pass->initialize(&ui_init_info);

        MainCameraPassInitInfo main_camera_init_info;
        m_main_camera_pass = std::make_shared<MainCameraPass>();
        m_main_camera_pass->initialize(&main_camera_init_info);
    }
    void RenderPipeline::preparePassData(std::shared_ptr<RenderResource> render_resource)
    {
        //m_main_camera_pass->preparePassData(render_resource);
        //m_pick_pass->preparePassData(render_resource);
        //m_directional_light_pass->preparePassData(render_resource);
        //m_point_light_shadow_pass->preparePassData(render_resource);
        //m_particle_pass->preparePassData(render_resource);
        //g_runtime_global_context.m_debugdraw_manager->preparePassData(render_resource);
    }

    void RenderPipeline::forwardRender(std::shared_ptr<RHI> rhi, std::shared_ptr<RenderResource> render_resource)
    {
        m_ui_pass->draw();
    }

    void RenderPipeline::deferredRender(std::shared_ptr<RHI> rhi, std::shared_ptr<RenderResource> render_resource)
    {
    }

    void RenderPipeline::initializeUIRenderBackend(WindowUI* window_ui)
    {
        m_ui_pass->initializeUIRenderBackend(window_ui);
    }
    uint32_t RenderPipeline::getGuidOfPickedMesh(const Vector2& picked_uv)
    {
        return 0;
    }
} // namespace Toon
