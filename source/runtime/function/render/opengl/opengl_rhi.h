#pragma once
#include "runtime/core/base/error.h"
#include "runtime/core/color/color.h"
#include "runtime/core/math/math_headers.h"

namespace Toon
{
	class WindowSystem;
	class OpenGLVertexArray;
	

	struct RHIInitInfo
	{
		std::shared_ptr<WindowSystem> window_system;
	};


	class OpenGLRHI
	{
	public:
		OpenGLRHI();
		~OpenGLRHI();
		void Initialize(RHIInitInfo info);
		void ClearColor(const Color&);
		void Clear();
		void DrawIndex(OpenGLVertexArray& vertexarray);
		void DrawArrays(OpenGLVertexArray& vertexarray, size_t count, int first = 0) ;
		void DrawArrays(OpenGLVertexArray& vertexarray, size_t count, unsigned int renderingMode, int first) ;
		void DrawInstancedArrays(OpenGLVertexArray& vertexarray, size_t count, size_t instance_count, int first = 0) ;
		void DrawArraysIndirect(OpenGLVertexArray& vertexarray, uint32_t& indirectBufferID) ;
		void DrawLine(OpenGLVertexArray& vertexarray, uint32_t count);
		void SetViewPort(unsigned int, unsigned int) ;
		Vector2 GetViewportSize() ;
	};
}