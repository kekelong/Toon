#include "runtime/function/render/passes/ui_pass.h"
#include "runtime/function/render/opengl/opengl_rhi.h"
#include "runtime/resource/config_manager.h"
#include "runtime/function/global/global_context.h"
#include "runtime/function/render/window_system.h"
#include "runtime/function/ui/window_ui.h"
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>

namespace Toon
{
    void UIPass::initialize(const RenderPassInitInfo* init_info)
    {
        RenderPass::initialize(nullptr);
    }

    void UIPass::initializeUIRenderBackend(WindowUI* window_ui)
    {
        m_window_ui = window_ui;

        const char* glsl_version = "#version 130";
        ImGui_ImplGlfw_InitForOpenGL(g_runtime_global_context.m_window_system->getWindow(), true);
        ImGui_ImplOpenGL3_Init(glsl_version);

        uploadFonts();
    }

    void UIPass::uploadFonts()
    {

    }

    void UIPass::draw()
    {
        if (m_window_ui)
        {
            // Start the Dear ImGui frame
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            m_window_ui->preRender();

            // Rendering
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        }
    }
} // namespace Toon
