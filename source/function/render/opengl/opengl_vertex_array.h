#pragma once
#include <memory>
#include "function/render/opengl/opengl_buffer.h"


namespace Toon {

	class OpenGLVertexArray
	{
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray();

		void Bind() const;
		void Unbind() const;

		void AddVertexBuffer(const std::shared_ptr<OpenGLVertexBuffer>& vertexBuffer) ;
		void SetIndexBuffer(const std::shared_ptr<OpenGLIndexBuffer>& indexBuffer) ;

		const std::vector<std::shared_ptr<OpenGLVertexBuffer>>& GetVertexBuffers() const { return m_VertexBuffers; }
		const std::shared_ptr<OpenGLIndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; }
	private:
		uint32_t m_RendererID;
		uint32_t m_VertexBufferIndex = 0;
		std::vector<std::shared_ptr<OpenGLVertexBuffer>> m_VertexBuffers;
		std::shared_ptr<OpenGLIndexBuffer> m_IndexBuffer;
	};

}
