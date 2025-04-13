#pragma once

#include <array>
#include <memory>
#include <optional>
#include"runtime/core/color/color.h"

namespace Toon
{
	class OpenGLRHI;
	class WindowSystem;
	class WindowUI;
	class ShaderLibrary;
	class RenderCamera;

	struct RenderSystemInitInfo
	{
		std::shared_ptr<WindowSystem> window_system;
	};

	class RenderSystem
	{
	public:
		RenderSystem() = default;
		~RenderSystem();

		void initialize(RenderSystemInitInfo init_info);
		void tick(float delta_time);
		void clear();

	
		void onWindowSize(int width, int height);

	private:
		void processSwapData();
		void setClearColor(const Color& color);
		void clearColor();

	private:       	
		std::shared_ptr<WindowSystem>				window_system;
		std::shared_ptr<ShaderLibrary>				shader_library;
		std::shared_ptr<RenderCamera>				m_render_camera;
		std::shared_ptr<OpenGLRHI>					m_rhi;
	};

} // namespace Toon
