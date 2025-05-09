#include "runtime/core/base/macro.h"
#include "runtime/core/base/error.h"
#include "runtime/function/render/opengl/opengl_vertex_array.h"

namespace Toon
{
	unsigned int GetSize(DataType type) {
		switch (type) {
		case DataType::Float:  return 1;
		case DataType::Float2: return  2;
		case DataType::Float3: return  3;
		case DataType::Float4: return  4;
		case DataType::Int:    return 1;
		case DataType::Int2:   return  2;
		case DataType::Int3:   return  3;
		case DataType::Int4:   return  4;
		case DataType::Mat2:   return 2 * 2;
		case DataType::Mat3:   return 3 * 3;
		case DataType::Mat4:   return 4 * 4;
		default:
			LOG_ERROR("Unidentfied Type");
		}
	}

	GLenum GetType(DataType type) {
		switch (type) {
		case DataType::Float:  return GL_FLOAT;
		case DataType::Float2: return GL_FLOAT;
		case DataType::Float3: return GL_FLOAT;
		case DataType::Float4: return GL_FLOAT;
		case DataType::Int:    return GL_INT;
		case DataType::Int2:   return GL_INT;
		case DataType::Int3:   return GL_INT;
		case DataType::Int4:   return GL_INT;
		case DataType::Mat2:   return GL_FLOAT;
		case DataType::Mat3:   return GL_FLOAT;
		case DataType::Mat4:   return GL_FLOAT;
		default:
			LOG_ERROR("Unidentfied Type");
		}
	}
	OpenGlVertexArray::OpenGlVertexArray()
	{
		glGenVertexArrays(1, &m_Renderer);
		glBindVertexArray(m_Renderer);
	}
	OpenGlVertexArray::~OpenGlVertexArray()
	{
		glDeleteVertexArrays(1, &m_Renderer);
	}
	void OpenGlVertexArray::Bind() const
	{
		glBindVertexArray(m_Renderer);
	}
	void OpenGlVertexArray::UnBind() const
	{
		glBindVertexArray(0);
	}
	void OpenGlVertexArray::AddBuffer(std::shared_ptr<BufferLayout>& layout, std::shared_ptr<VertexBuffer>& vbo)
	{
		vbo->Bind();
		Bind();
		auto element = layout->GetElements();
		int size = element.size();
		int offset = 0;
		for (unsigned int i = 0; i < size; i++)
		{
			glEnableVertexAttribArray(i);
			glVertexAttribPointer(i, GetSize(element[i]->Type), GetType(element[i]->Type), element[i]->Normalized, layout->GetStride(), (const void*)offset);
			offset += GetSize(element[i]->Type) * sizeof(GetType(element[i]->Type));
		}

		m_VertexBuffer.push_back(vbo);
	}
	void OpenGlVertexArray::SetIndexBuffer(std::shared_ptr<IndexBuffer> IndexBuffer)
	{
		Bind();
		IndexBuffer->Bind();
		m_IndexBuffer = IndexBuffer;
	}
}
