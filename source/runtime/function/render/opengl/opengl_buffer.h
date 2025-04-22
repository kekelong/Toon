#pragma once
#include "runtime/core/base/error.h"
#include "runtime/function/render/opengl/interface/rhi_buffer.h"

namespace Toon
{
	class OpenGlVertexBuffer : public VertexBuffer 
	{
	public:
		OpenGlVertexBuffer(float* data, size_t size);
		OpenGlVertexBuffer(size_t size, BufferStorage_Type Storage_Type = MUTABLE);
		~OpenGlVertexBuffer();
		virtual void Bind() const override;
		virtual void UnBind() const override;
		virtual void SetData(size_t size, const void* data) override;
		virtual void* MapBuffer(size_t size) override;
	private:
		uint32_t m_RendererID;
	};


	class OpenGlIndexBuffer : public IndexBuffer 
	{
	public:
		OpenGlIndexBuffer(uint32_t* data, size_t size);
		~OpenGlIndexBuffer();
		void Bind() const override;
		void UnBind() const override;
		size_t GetCount()override;
	private:
		size_t m_Elements;
		uint32_t m_RendererID;
	};
}