#include "runtime/function/render/opengl/interface/rhi_buffer.h"
#include "runtime/function/render/opengl/opengl_buffer.h"
#include "runtime/function/render/opengl/opengl_vertex_array.h"

namespace Toon
{
	std::shared_ptr<VertexBuffer> VertexBuffer::Create(float* data, size_t size)
	{
		return std::make_shared<OpenGlVertexBuffer>(data, size);
	}

	std::shared_ptr<VertexBuffer> VertexBuffer::Create(size_t size, BufferStorage_Type Storage_Type)
	{
		return std::make_shared<OpenGlVertexBuffer>(size, Storage_Type);
	}

	/// //////////////////////////////////////////////////////////////////////////

	std::shared_ptr<IndexBuffer> IndexBuffer::Create(uint32_t* data, size_t size)
	{
		return std::make_shared<OpenGlIndexBuffer>(data, size);
	}


	/// ////////////////////////////////////////////////////////////////////////////

	void BufferLayout::push(std::string name, DataType type)
	{
		m_Elements.push_back(new BufferElements(name, type));
		Stride += GetSize(type);
	}
	unsigned int BufferLayout::GetSize(DataType type)
	{
		switch (type) {
		case DataType::Float: return sizeof(float);
		case DataType::Float2: return sizeof(float) * 2;
		case DataType::Float3: return sizeof(float) * 3;
		case DataType::Float4: return sizeof(float) * 4;
		case DataType::Int: return sizeof(int);
		case DataType::Int2: return sizeof(int) * 2;
		case DataType::Int3: return sizeof(int) * 3;
		case DataType::Int4: return sizeof(int) * 4;
		case DataType::Mat2: return sizeof(float) * 2 * 2;
		case DataType::Mat3: return sizeof(float) * 3 * 3;
		case DataType::Mat4: return sizeof(float) * 4 * 4;
		default:
			LOG_ERROR("Unidentfied Type");
		}
		return -1;
	}

	/////////////////////////////////////////////////////////////////////////

	std::shared_ptr<VertexArray> VertexArray::Create()
	{
		return std::make_shared<OpenGlVertexArray>();
	}
}