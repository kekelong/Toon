#include "runtime/function/render/opengl/opengl_rhi.h"
#include "runtime/function/render/opengl/opengl_vertex_array.h"
namespace Toon
{
	OpenGLRHI::OpenGLRHI()
	{

	}
	OpenGLRHI::~OpenGLRHI()
	{
	}

	void OpenGLRHI::Initialize(RHIInitInfo info)
	{
		int MaxTextureImageUnits;
		glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &MaxTextureImageUnits);
		LOG_INFO("Number of texture slots available are :- {}", MaxTextureImageUnits);

		//glEnable(GL_DEBUG_OUTPUT);
		//glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		//glDebugMessageCallback(glDebugOutput, nullptr);
		//glEnable(GL_MULTISAMPLE);
		//glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE_ARB);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		//glEnable(GL_STENCIL_TEST);
		glEnable(GL_LINE_SMOOTH);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
	}

	void OpenGLRHI::ClearColor(const Color& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRHI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}

	void OpenGLRHI::DrawIndex(VertexArray& vertexarray)
	{
		vertexarray.Bind();
		glDrawElements(GL_TRIANGLES, vertexarray.GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, (const void*)0);
	}

	void OpenGLRHI::DrawArrays(VertexArray& vertexarray, size_t count, int first)
	{
		vertexarray.Bind();
		glDrawArrays(GL_TRIANGLES, first, count);
	}

	void OpenGLRHI::DrawArrays(VertexArray& vertexarray, size_t count, unsigned int renderingMode, int first)
	{
		vertexarray.Bind();
		glDrawArrays(renderingMode, first, count);
	}

	void OpenGLRHI::DrawInstancedArrays(VertexArray& vertexarray, size_t count, size_t instance_count, int first)
	{
		vertexarray.Bind();
		glDrawArraysInstanced(GL_TRIANGLES, first, count, instance_count);
		int size = sizeof(int) * 4;
	}

	void OpenGLRHI::DrawArraysIndirect(VertexArray& vertexarray, uint32_t& indirectBufferID)
	{
		glBindBuffer(GL_DRAW_INDIRECT_BUFFER, indirectBufferID);
		vertexarray.Bind();
		glDrawArraysIndirect(GL_TRIANGLES, 0);
	}

	void OpenGLRHI::DrawLine(VertexArray& vertexarray, uint32_t count)
	{
		vertexarray.Bind();
		glDrawArrays(GL_LINES, 0, count);
	}
	
	void OpenGLRHI::SetViewPort(unsigned int Width, unsigned int Height)
	{
		glViewport(0, 0, Width, Height);
	}

	Vector2 OpenGLRHI::GetViewportSize()
	{
		float arr[4];
		glGetFloatv(GL_VIEWPORT, arr);
		return { arr[2],arr[3] };//the index 2 and 3 gives the width and height of the viewport
	}
}