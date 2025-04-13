#pragma once
#include "runtime/core/base/error.h"
#include "runtime/core/math/math_headers.h"
#include <string>
namespace Toon
{
	class OpenGlTexture2D
	{
	public:
		OpenGlTexture2D(const std::string& path, bool bUse16BitTexture = false);
		OpenGlTexture2D(const uint32_t Width = 1, const uint32_t Height = 1, uint32_t data = 0xffffffff);
		~OpenGlTexture2D();
	public:
		uint32_t	GetWidth()  { return m_Width; }
		uint32_t	GetHeight()  { return m_Height; }
		uint32_t	GetChannels()  { return channels; }
		void		Bind(int slot)const ;
		void		UnBind()const ;
		uint32_t	GetID()  { return m_Renderid; }
		uint16_t*	GetTexture()  { return pixel_data_16; }
	private:
		int			m_Width;
		int			m_Height;
		int			channels;
		uint32_t	m_Renderid;
		uint16_t*	resized_image_16	= nullptr;
		uint16_t*	pixel_data_16		= nullptr;
		uint8_t*	resized_image_8		= nullptr;
		uint8_t*	pixel_data_8		= nullptr;
	private:
		void Resize_Image(const float& width, const float& height, bool bUse16BitTexture = false);
		void Create16BitTexture(const std::string& path);
		void Create8BitsTexture(const std::string& path);
		void CreateWhiteTexture();
	};
}