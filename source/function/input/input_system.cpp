#include "core/base/macro.h"
#include "function/input/input_system.h"
#include "function/global/global_context.h"
#include "function/render/window_system.h"

//#include "core/glad/glad.h"
#include <GLFW/glfw3.h>

namespace Toon
{

    void InputSystem::onKey(int key, int scancode, int action, int mods)
    {
		if (action == GLFW_PRESS)
		{
			switch (key)
			{
			case GLFW_KEY_ESCAPE:
				// close();
				break;
			case GLFW_KEY_R:
				break;
			case GLFW_KEY_A:

				break;
			case GLFW_KEY_S:
				break;
			case GLFW_KEY_W:

				break;
			case GLFW_KEY_D:

				break;
			case GLFW_KEY_SPACE:

				break;
			case GLFW_KEY_LEFT_CONTROL:

				break;
			case GLFW_KEY_LEFT_ALT: {

			}
								  break;
			case GLFW_KEY_LEFT_SHIFT:

				break;
			case GLFW_KEY_F:

				break;
			default:
				break;
			}
		}
		else if (action == GLFW_RELEASE)
		{
			switch (key)
			{
			case GLFW_KEY_ESCAPE:
				// close();
				break;
			case GLFW_KEY_R:
				LOG_INFO("R................");
				break;
			case GLFW_KEY_W:
				LOG_INFO("W................");
				break;
			case GLFW_KEY_S:
				LOG_INFO("S................");
				break;
			case GLFW_KEY_A:
				LOG_INFO("A................");
				break;
			case GLFW_KEY_D:
				LOG_INFO("D...............");
				break;
			case GLFW_KEY_LEFT_CONTROL:
				LOG_INFO("CONTROL................");
				break;
			case GLFW_KEY_LEFT_SHIFT:
				LOG_INFO("SHIFT................");
				break;
			default:
				break;
			}
		}
    }


    void InputSystem::onCursorPos(double current_cursor_x, double current_cursor_y)
    {

    }

    void InputSystem::clear()
    {
        m_cursor_delta_x = 0;
        m_cursor_delta_y = 0;
    }

    void InputSystem::calculateCursorDeltaAngles()
    {
		/* std::array<int, 2> window_size = g_runtime_global_context.m_window_system->getWindowSize();

		 if (window_size[0] < 1 || window_size[1] < 1)
		 {
			 return;
		 }

		 std::shared_ptr<RenderCamera> render_camera = g_runtime_global_context.m_render_system->getRenderCamera();
		 const Vector2&                fov           = render_camera->getFOV();

		 Radian cursor_delta_x(Math::degreesToRadians(m_cursor_delta_x));
		 Radian cursor_delta_y(Math::degreesToRadians(m_cursor_delta_y));

		 m_cursor_delta_yaw   = (cursor_delta_x / (float)window_size[0]) * fov.x;
		 m_cursor_delta_pitch = -(cursor_delta_y / (float)window_size[1]) * fov.y;*/
    }

    void InputSystem::initialize()
    {
		LOG_INFO("InputSystem initialize");
        std::shared_ptr<WindowSystem> window_system = g_runtime_global_context.m_window_system;
        ASSERT(window_system);

        window_system->registerOnKeyFunc(std::bind(&InputSystem::onKey,
                                                   this,
                                                   std::placeholders::_1,
                                                   std::placeholders::_2,
                                                   std::placeholders::_3,
                                                   std::placeholders::_4));
        window_system->registerOnCursorPosFunc(
            std::bind(&InputSystem::onCursorPos, this, std::placeholders::_1, std::placeholders::_2));
    }

    void InputSystem::tick()
    {
        calculateCursorDeltaAngles();
        clear();
    }
} // namespace Toon
