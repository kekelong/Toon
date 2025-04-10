#include "core/base/error.h"
#include "function/ui/window_ui.h"
#include "function/render/render_imgui.h"
#include "function/render/window_system.h"
#include "function/global/global_context.h"
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>

namespace Toon {

	void Toon::RenderImgui::initialize(WindowUI* window_ui)
	{
		LOG_INFO("RenderImgui initialize");

		m_window_ui = window_ui;

		const char* glsl_version = "#version 130";
		ImGui_ImplGlfw_InitForOpenGL(g_runtime_global_context.m_window_system->getWindow(), true);
		ImGui_ImplOpenGL3_Init(glsl_version);	
	}

	void RenderImgui::tick(float delta_time)
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

	void Toon::RenderImgui::clear()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}
}