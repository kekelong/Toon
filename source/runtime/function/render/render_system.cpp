#include "runtime/core/base/macro.h"
#include "runtime/core/base/error.h"
#include "runtime/function/render/render_camera.h"
#include "runtime/function/render/render_system.h"
#include "runtime/function/global/global_context.h"
#include "runtime/function/render/window_system.h"
#include "runtime/function/render/debugdraw/debug_draw_manager.h"
#include "runtime/function/render/opengl/opengl_shader.h"
#include "runtime/function/render/opengl/opengl_rhi.h"
#include "runtime/resource/config_manager.h"

namespace Toon
{
	RenderSystem::~RenderSystem()
	{
		clear();
	}
	void RenderSystem::initialize(RenderSystemInitInfo init_info)
	{
		LOG_INFO("RenderSystem initialize");

		std::shared_ptr<ConfigManager> config_manager = g_runtime_global_context.m_config_manager;
		ASSERT(config_manager);
		std::shared_ptr<AssetManager> asset_manager = g_runtime_global_context.m_asset_manager;
		ASSERT(asset_manager);

		RHIInitInfo rhi_init_info;
		rhi_init_info.window_system = init_info.window_system;
		m_rhi = std::make_shared<OpenGLRHI>();
		m_rhi->Initialize(rhi_init_info);

		shader_library = std::make_shared<ShaderLibrary>();
		m_render_camera = std::make_shared<RenderCamera>();

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


		g_runtime_global_context.m_debugdraw_manager->tick(delta_time);
	}

	void RenderSystem::clear()
	{
		g_runtime_global_context.m_debugdraw_manager->clear();
	}


	void RenderSystem::onWindowSize(int width, int height)
	{
		m_rhi->SetViewPort(width, height);
	}

	void RenderSystem::processSwapData()
	{

	}
	 
	void RenderSystem::setClearColor(const Color& color)
	{
		m_rhi->ClearColor(color);
	}

	void RenderSystem::clearColor()
	{
		m_rhi->Clear();
	}

}

