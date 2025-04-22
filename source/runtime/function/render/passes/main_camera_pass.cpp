#include "runtime/function/render/passes/main_camera_pass.h"
#include "runtime/function/render/render_helper.h"
#include "runtime/function/render/render_resource.h"

#include "runtime/function/render/opengl/opengl_rhi.h"

#include <map>
#include <stdexcept>
namespace Toon
{
    void MainCameraPass::initialize(const RenderPassInitInfo* init_info)
    {
        RenderPass::initialize(init_info);
        const MainCameraPassInitInfo* _init_info = static_cast<const MainCameraPassInitInfo*>(init_info);
        m_enable_fxaa = _init_info->enble_fxaa;
    }


    void MainCameraPass::preparePassData(std::shared_ptr<RenderResource> render_resource)
    {

    }

    void MainCameraPass::draw(UIPass& ui_pass)
    {     
        ui_pass.draw();
    }

    void MainCameraPass::drawForward(UIPass& ui_pass)
    {
      
        ui_pass.draw();
    }


} // namespace Toon
