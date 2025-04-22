#pragma once

#include "runtime/function/render/render_pass.h"

#include "runtime/function/render/passes/ui_pass.h"

namespace Toon
{
    class RenderResource;

    struct MainCameraPassInitInfo : RenderPassInitInfo
    {
        bool enble_fxaa;
    };

    class MainCameraPass : public RenderPass
    {
    public:

        void initialize(const RenderPassInitInfo* init_info) override final;

        void preparePassData(std::shared_ptr<RenderResource> render_resource) override final;

        void draw(UIPass& ui_pass);

        void drawForward(UIPass& ui_pass);

    private:
        bool m_enable_fxaa{ false };
    };
} // namespace Toon
