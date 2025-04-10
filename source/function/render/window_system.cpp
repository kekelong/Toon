#include "function/render/window_system.h"
#include "core/base/macro.h"



namespace Toon
{
	static void glfw_error_callback(int error, const char* description)
	{
		LOG_ERROR("GLFW Error %d: %s\n", error, description);
	}

	WindowSystem::~WindowSystem()
	{
		glfwDestroyWindow(m_window);
		glfwTerminate();
	}

	void WindowSystem::initialize(WindowCreateInfo create_info)
	{
		LOG_INFO("WindowSystem initialize");

		glfwSetErrorCallback(glfw_error_callback);
		if (!glfwInit())
		{
			LOG_FATAL(__FUNCTION__, "failed to initialize GLFW");
			return;
		}

		m_width = create_info.width;
		m_height = create_info.height;

		//设置OpenGL主版本号、次版本号
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		//设置OpenGL启用核心模式（非立即渲染模式）
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		m_window = glfwCreateWindow(create_info.width, create_info.height, create_info.title, nullptr, nullptr);
		if (!m_window)
		{
			LOG_FATAL(__FUNCTION__, "failed to create window");
			glfwTerminate();
			return;
		}
		glfwMakeContextCurrent(m_window);
		glfwSwapInterval(1); // Enable vsync
		/*检查GLAD库的初始化是否成功。
		 * gladLoadGLLoader函数是GLAD库提供的函数，用于加载OpenGL函数指针。
	     * glfwGetProcAddress函数是GLFW库提供的函数，用于获取特定OpenGL函数的地址。*/
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			LOG_FATAL(__FUNCTION__, "Failed to initialize GLAD");
			return ;
		}

		glfwSetFramebufferSizeCallback(m_window, frameBufferSizeCallback);

		// Setup input callbacks
		glfwSetWindowUserPointer(m_window, this);
		glfwSetKeyCallback(m_window, keyCallback);
		glfwSetCharCallback(m_window, charCallback);
		glfwSetCharModsCallback(m_window, charModsCallback);
		glfwSetMouseButtonCallback(m_window, mouseButtonCallback);
		glfwSetCursorPosCallback(m_window, cursorPosCallback);
		glfwSetCursorEnterCallback(m_window, cursorEnterCallback);
		glfwSetScrollCallback(m_window, scrollCallback);
		glfwSetDropCallback(m_window, dropCallback);
		glfwSetWindowSizeCallback(m_window, windowSizeCallback);
		glfwSetWindowCloseCallback(m_window, windowCloseCallback);
	}

	void WindowSystem::pollEvents() const { glfwPollEvents(); }

	bool WindowSystem::shouldClose() const { return glfwWindowShouldClose(m_window); }

	void WindowSystem::swapBuffers() const { glfwSwapBuffers(m_window); }

	void WindowSystem::setTitle(const char* title) { glfwSetWindowTitle(m_window, title); }

	GLFWwindow* WindowSystem::getWindow() const { return m_window; }

	std::array<int, 2> WindowSystem::getWindowSize() const { return std::array<int, 2>({ m_width, m_height }); }

} // namespace Toon
