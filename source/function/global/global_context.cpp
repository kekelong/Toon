#pragma once

#include "core/log/log_system.h"
#include "function/render/window_system.h"
#include "function/render/render_system.h"
#include "function/global/global_context.h"
#include "function/input/input_system.h"
#include "resource/config_manager.h"
#include "resource/asset_manager.h"
#include "function/render/debugdraw/debug_draw_manager.h"
namespace Toon
{
	RuntimeGlobalContext g_runtime_global_context;

	void RuntimeGlobalContext::startSystems(const std::string& config_file_path)
	{
		m_config_manager = std::make_shared<ConfigManager>();
		m_config_manager->initialize(config_file_path);

		m_asset_manager = std::make_shared<AssetManager>();

		m_window_system = std::make_shared<WindowSystem>();
		WindowCreateInfo window_create_info;
		m_window_system->initialize(window_create_info);
		
		m_render_system = std::make_shared<RenderSystem>();
		RenderSystemInitInfo render_init_info;
		render_init_info.window_system = m_window_system;
		m_render_system->initialize(render_init_info);

		m_debugdraw_manager = std::make_shared<DebugDrawManager>();
		m_debugdraw_manager->initialize();

		m_input_system = std::make_shared<InputSystem>();
		m_input_system->initialize();
	}

	void RuntimeGlobalContext::shutdownSystems()
	{
        m_render_system.reset();
		m_window_system.reset();
        m_logger_system.reset();
		m_debugdraw_manager.reset();

	}
	void RuntimeGlobalContext::initLogSystem()
	{
		m_logger_system = std::make_shared<LogSystem>();
	}
} // namespace Toon
