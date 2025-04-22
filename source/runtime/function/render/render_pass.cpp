#include "runtime/function/render/render_pass.h"

#include "runtime/core/base/macro.h"

namespace Toon
{
    VisiableNodes RenderPass::m_visiable_nodes;

    void RenderPass::initialize(const RenderPassInitInfo* init_info)
    {
    }

    void RenderPass::postInitialize() {}
    void RenderPass::setCommonInfo(RenderPassCommonInfo common_info)
    {
        m_rhi = common_info.rhi;
        m_render_resource = common_info.render_resource;
    }
    void RenderPass::preparePassData(std::shared_ptr<RenderResource> render_resource) {}
    void RenderPass::initializeUIRenderBackend(WindowUI* window_ui) {}

    void RenderPass::draw() {}

} // namespace Toon
