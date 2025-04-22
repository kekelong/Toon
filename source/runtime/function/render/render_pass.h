#pragma once

#include "runtime/function/render/opengl/opengl_rhi.h"

namespace Toon
{
    class OpenGLRHI;
    class RenderResource;
    class WindowUI;
    class OpenGlFrameBuffer;
    class RenderMeshNode;

    struct VisiableNodes
    {
        std::vector<RenderMeshNode>* p_directional_light_visible_mesh_nodes{ nullptr };
        std::vector<RenderMeshNode>* p_point_lights_visible_mesh_nodes{ nullptr };
        std::vector<RenderMeshNode>* p_main_camera_visible_mesh_nodes{ nullptr };
    };

    struct RenderPassInitInfo
    {
    };

    struct RenderPassCommonInfo
    {
        std::shared_ptr<OpenGLRHI>                  rhi;
        std::shared_ptr<RenderResource>             render_resource;
    };

    class RenderPass
    {
    public:
        static VisiableNodes m_visiable_nodes;

    public:
        virtual void initialize(const RenderPassInitInfo* init_info);
        virtual void postInitialize();
        virtual void setCommonInfo(RenderPassCommonInfo common_info);
        virtual void preparePassData(std::shared_ptr<RenderResource> render_resource);
        virtual void initializeUIRenderBackend(WindowUI* window_ui);
        virtual void draw();
    protected:
        std::shared_ptr<OpenGlFrameBuffer>          m_framebuffer;                            
        std::shared_ptr<OpenGLRHI>                  m_rhi;
        std::shared_ptr<RenderResource>             m_render_resource;
    };
} // namespace Toon
