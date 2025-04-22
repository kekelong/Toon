#include "runtime/engine.h"
#include "runtime/core/base/macro.h"
#include "runtime/function/global/global_context.h"
#include "runtime/function/render/render_system.h"
#include "runtime/function/render/window_system.h"
#include "runtime/function/input/input_system.h"
#include "runtime/core/meta/reflection/reflection_register.h"
#include "runtime/function/framework/world/world_manager.h"
namespace Toon
{
	void ToonEngine::startEngine(const std::string& config_file_path)
	{
		Reflection::TypeMetaRegister::metaRegister();
		g_runtime_global_context.startSystems(config_file_path);
		LOG_INFO("engine start");
	}

	void ToonEngine::shutdownEngine()
	{
		LOG_INFO("engine shutdown");
		g_runtime_global_context.shutdownSystems();	
	}

	void ToonEngine::initialize() 
	{
		g_runtime_global_context.initLogSystem();
	}
	void ToonEngine::clear() {}

	void ToonEngine::run()
	{
		float delta_time;
		while (true)
		{
			delta_time = calculateDeltaTime();
			if (!tickOneFrame(delta_time))
				return;
		}
	}

	float ToonEngine::calculateDeltaTime()
	{
		float delta_time;
		{
			using namespace std::chrono;

			steady_clock::time_point tick_time_point = steady_clock::now();
			duration<float> time_span = duration_cast<duration<float>>(tick_time_point - m_last_tick_time_point);
			delta_time = time_span.count();

			m_last_tick_time_point = tick_time_point;
		}
		return delta_time;
	}

	bool ToonEngine::tickOneFrame(float delta_time)
	{
		logicalTick(delta_time);
		calculateFPS(delta_time);
		rendererTick(delta_time);

		g_runtime_global_context.m_window_system->pollEvents();

		g_runtime_global_context.m_window_system->setTitle(
			std::string("Toon - " + std::to_string(getFPS()) + " FPS").c_str());
		g_runtime_global_context.m_window_system->swapBuffers();
		const bool should_window_close = g_runtime_global_context.m_window_system->shouldClose();
		return !should_window_close;
	}

	void ToonEngine::logicalTick(float delta_time)
	{
		g_runtime_global_context.m_world_manager->tick(delta_time);
		g_runtime_global_context.m_input_system->tick();
	}

	bool ToonEngine::rendererTick(float delta_time)
	{
		g_runtime_global_context.m_render_system->tick(delta_time);
		return true;
	}

	const float ToonEngine::s_fps_alpha = 1.f / 100;
	void ToonEngine::calculateFPS(float delta_time)
	{
		m_frame_count++;
		if (m_frame_count == 1)
		{
			m_average_duration = delta_time;
		}
		else
		{
			m_average_duration = m_average_duration * (1 - s_fps_alpha) + delta_time * s_fps_alpha;
		}

		m_fps = static_cast<int>(1.f / m_average_duration);
	}
} // namespace Toon
