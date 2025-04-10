#pragma once

#include <array>
#include <memory>
#include <optional>

#include"core/color/color.h"

namespace Toon
{
	class WindowSystem;
	class WindowUI;
	class RenderImgui;
	class ShaderLibrary;

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

		void initializeImgui(WindowUI* window_ui);
	
		void onWindowSize(int width, int height);

	private:
		void processSwapData();
		void setClearColor(const Color& color);
		void clearColor();

	private:       
		std::shared_ptr<RenderImgui>                m_render_imgui;		
		std::shared_ptr<WindowSystem>				window_system;
		std::shared_ptr<ShaderLibrary>				shader_library;
	};

} // namespace Toon
