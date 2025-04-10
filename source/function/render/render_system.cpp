#include "core/base/macro.h"
#include "core/base/error.h"
#include "function/render/render_system.h"
#include "function/global/global_context.h"
#include "function/render/window_system.h"
#include "function/render/render_imgui.h"
#include "function/render/debugdraw/debug_draw_manager.h"
#include "function/render/opengl/opengl_shader.h"
#include "resource/config_manager.h"

namespace Toon
{
	RenderSystem::~RenderSystem()
	{
		clear();
	}
	void RenderSystem::initialize(RenderSystemInitInfo init_info)
	{
		LOG_INFO("RenderSystem initialize");

		shader_library = std::make_shared<ShaderLibrary>();

		std::filesystem::path shaderpath = g_runtime_global_context.m_config_manager->getAssetFolder() / "shaders/test.glsl";
		shader_library->Load(shaderpath.generic_string());

		window_system = init_info.window_system;
		ASSERT(window_system);	
		window_system->registerOnWindowSizeFunc(std::bind(&RenderSystem::onWindowSize,
			this,
			std::placeholders::_1,
			std::placeholders::_2));
		setClearColor({ 0.1f, 0.1f, 0.1f, 1.f });
	}

	void RenderSystem::tick(float delta_time)
	{
		clearColor();

		processSwapData();

		m_render_imgui->tick(delta_time);

		g_runtime_global_context.m_debugdraw_manager->tick(delta_time);
	}

	void RenderSystem::clear()
	{
		g_runtime_global_context.m_debugdraw_manager->clear();
		m_render_imgui->clear();
	}

	void RenderSystem::initializeImgui(WindowUI* window_ui)
	{
		m_render_imgui = std::make_shared<RenderImgui>();
		m_render_imgui->initialize(window_ui);
	}

	void RenderSystem::onWindowSize(int width, int height)
	{
		GL_CALL(glViewport(0, 0, width, height));
	}

	void RenderSystem::processSwapData()
	{

	}

	void RenderSystem::setClearColor(const Color& color)
	{
		GL_CALL(glClearColor(color.r, color.g, color.b, color.a));
	}

	void RenderSystem::clearColor()
	{
		GL_CALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	}

}

