#pragma once

#include <array>
#include <memory>
#include <optional>
#include"runtime/core/color/color.h"
#include "runtime/function/render/render_entity.h"
#include "runtime/function/render/render_swap_context.h"
#include "runtime/function/render/render_type.h"

namespace Toon
{
	class RHI;
	class WindowSystem;
	class WindowUI;
	class RenderCamera;
	class RenderPipeline;
	class RenderResource;
	class RenderScene;
	class RenderSwapContext;

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

		void							onWindowSize(int width, int height);
		void							swapLogicRenderData();
		RenderSwapContext&				getSwapContext();
		std::shared_ptr<RenderCamera>	getRenderCamera() const;
		std::shared_ptr<RHI>			getRHI() const;
		void							initializeUIRenderBackend(WindowUI* window_ui);
	private:
		void processSwapData();
	private:       	
		RenderSwapContext							m_swap_context;
		std::shared_ptr<RenderPipeline>				m_render_pipeline;
		std::shared_ptr<RenderResource>				m_render_resource;
		std::shared_ptr<WindowSystem>				window_system;
		std::shared_ptr<RenderCamera>				m_render_camera;
		std::shared_ptr<RenderScene>				m_render_scene;
		std::shared_ptr<RHI>						m_rhi;
	};

} // namespace Toon
