#pragma once
#include "runtime/core/base/error.h"
#include "runtime/core/color/color.h"
#include "runtime/core/math/math_headers.h"
#include "runtime/function/render/opengl/interface/rhi_texture.h"
#include "runtime/function/render/opengl/interface/rhi_shader.h"
#include "runtime/function/render/opengl/interface/rhi_buffer.h"
#include "runtime/function/render/opengl/interface/rhi_framebuffer.h"

namespace Toon
{
	struct RHIInitInfo;

	class RHI
	{
	public:
		virtual ~RHI() {};
		virtual void Initialize(RHIInitInfo info) = 0;
		virtual void ClearColor(const Color&) = 0;
		virtual void Clear() = 0;
		virtual void DrawIndex(VertexArray& vertexarray) = 0;
		virtual void DrawArrays(VertexArray& vertexarray, size_t count, int first = 0) = 0;
		virtual void DrawArrays(VertexArray& vertexarray, size_t count, unsigned int renderingMode, int first) = 0;
		virtual void DrawInstancedArrays(VertexArray& vertexarray, size_t count, size_t instance_count, int first = 0) = 0;
		virtual void DrawArraysIndirect(VertexArray& vertexarray, uint32_t& indirectBufferID) = 0;
		virtual void DrawLine(VertexArray& vertexarray, uint32_t count) = 0;
		virtual void SetViewPort(unsigned int, unsigned int) = 0;
		virtual Vector2 GetViewportSize() = 0;
	};
}