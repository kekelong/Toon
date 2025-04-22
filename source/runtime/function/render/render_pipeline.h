#pragma once

#include "runtime/core/math/vector2.h"

#include <memory>
#include <vector>

namespace Toon
{
    class RHI;
    class RenderResource;
    class WindowUI;
    class RenderPass;

    struct RenderPipelineInitInfo
    {
        bool                            enable_fxaa{ false };
        std::shared_ptr<RenderResource> render_resource;
    };

    class RenderPipeline
    {
        friend class RenderSystem;

    public:
        ~RenderPipeline() {}

        void clear() {};

        void initialize(RenderPipelineInitInfo init_info);

        void preparePassData(std::shared_ptr<RenderResource> render_resource);
        void forwardRender(std::shared_ptr<RHI> rhi, std::shared_ptr<RenderResource> render_resource);
        void deferredRender(std::shared_ptr<RHI> rhi, std::shared_ptr<RenderResource> render_resource);

        void             initializeUIRenderBackend(WindowUI* window_ui);
        uint32_t getGuidOfPickedMesh(const Vector2& picked_uv);

    protected:
        std::shared_ptr<RHI> m_rhi;


        std::shared_ptr<RenderPass> m_main_camera_pass;
        std::shared_ptr<RenderPass> m_ui_pass;

    };
} // namespace Toon

