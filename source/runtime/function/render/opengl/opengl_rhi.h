#pragma once
#include "runtime/core/base/error.h"
#include "runtime/core/color/color.h"
#include "runtime/core/math/math_headers.h"
#include "runtime/function/render/opengl/interface/rhi.h"

namespace Toon
{
	class WindowSystem;
	class VertexArray;
	

	struct RHIInitInfo
	{
		std::shared_ptr<WindowSystem> window_system;
	};


	class OpenGLRHI : public RHI
	{
	public:
		OpenGLRHI();
		virtual ~OpenGLRHI();
		virtual void Initialize(RHIInitInfo info) override;
		virtual void ClearColor(const Color&) override;
		virtual void Clear() override;
		virtual void DrawIndex(VertexArray& vertexarray) override;
		virtual void DrawArrays(VertexArray& vertexarray, size_t count, int first = 0)  override;
		virtual void DrawArrays(VertexArray& vertexarray, size_t count, unsigned int renderingMode, int first)  override;
		virtual void DrawInstancedArrays(VertexArray& vertexarray, size_t count, size_t instance_count, int first = 0) override;
		virtual void DrawArraysIndirect(VertexArray& vertexarray, uint32_t& indirectBufferID) override;
		virtual void DrawLine(VertexArray& vertexarray, uint32_t count) override;
		virtual void SetViewPort(unsigned int, unsigned int)  override;
		virtual Vector2 GetViewportSize() override;
	};
}