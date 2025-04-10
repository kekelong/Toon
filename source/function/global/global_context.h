#pragma once

#include <memory>
#include <string>
namespace Toon
{
	class ConfigManager;
	class LogSystem;
	class WindowSystem;
	class RenderSystem;
	class InputSystem;
	class DebugDrawManager;
	class AssetManager;

	/// Manage the lifetime and creation/destruction order of all global system
	class RuntimeGlobalContext
	{
	public:
		// create all global systems and initialize these systems
		void startSystems(const std::string& config_file_path);
		// destroy all global systems
		void shutdownSystems();

		void initLogSystem();
	public:
		std::shared_ptr<ConfigManager>     m_config_manager;
		std::shared_ptr<LogSystem>         m_logger_system;
		std::shared_ptr<InputSystem>       m_input_system;
		std::shared_ptr<WindowSystem>      m_window_system;
		std::shared_ptr<RenderSystem>      m_render_system;
		std::shared_ptr<DebugDrawManager>  m_debugdraw_manager;
		std::shared_ptr<AssetManager>      m_asset_manager;
	};

	extern RuntimeGlobalContext g_runtime_global_context;
} // namespace Toon