#include "runtime/function/render/opengl/opengl_texture.h"
#include "runtime/function/global/global_context.h"
#include "runtime/resource/config_manager.h"
#include "runtime/resource/asset_manager.h"
#include "runtime/core/timer/timer.h"
#include <fstream>

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include <stb_image.h>
#include <stb_image_resize.h>


namespace Toon
{
	OpenGlTexture2D::OpenGlTexture2D(const std::string& path, bool bUse16BitTexture)
		:m_Height(0), m_Width(0)
	{
		if (bUse16BitTexture)
			Create16BitTexture(path);
		else
			Create8BitsTexture(path);
	}

	OpenGlTexture2D::OpenGlTexture2D(const uint32_t Width, const uint32_t Height, uint32_t data)
		:m_Height(Height), m_Width(Width)
	{
		GLenum InternalFormat = GL_RGBA8, Format = GL_RGBA;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_Renderid);
		glTextureStorage2D(m_Renderid, 1, InternalFormat, m_Width, m_Height);

		glTextureParameteri(m_Renderid, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_Renderid, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureSubImage2D(m_Renderid, 0, 0, 0, m_Width, m_Height, Format, GL_UNSIGNED_BYTE, &data);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void OpenGlTexture2D::Create16BitTexture(const std::string& path)
	{
		stbi_set_flip_vertically_on_load(1);
		pixel_data_16 = stbi_load_16(path.c_str(), &m_Width, &m_Height, &channels, 0);

		GLenum InternalFormat = 0, Format = 0;
		if (pixel_data_16 == nullptr) {
			LOG_ERROR("2D Image not found!!");
			CreateWhiteTexture();
		}
		else 
		{
			if (channels == 4)
			{
				InternalFormat = GL_RGBA16;
				Format = GL_RGBA;
			}
			else if (channels == 3)
			{
				InternalFormat = GL_RGB16;
				Format = GL_RGB;
			}
			else if (channels == 2)
			{
				InternalFormat = GL_RG16;
				Format = GL_RG;
			}
			else if (channels == 1)
			{
				InternalFormat = GL_R16;
				Format = GL_RED;
			}
			else
				LOG_ERROR("Invalid Texture format");

			glCreateTextures(GL_TEXTURE_2D, 1, &m_Renderid);
			glTextureStorage2D(m_Renderid, 1, InternalFormat, m_Width, m_Height);

			glGenerateTextureMipmap(m_Renderid);
			glTextureParameteri(m_Renderid, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTextureParameteri(m_Renderid, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_NEAREST);
			glTextureParameteri(m_Renderid, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTextureParameteri(m_Renderid, GL_TEXTURE_WRAP_R, GL_REPEAT);

			if (resized_image_16)
			{
				glTextureSubImage2D(m_Renderid, 0, 0, 0, m_Width, m_Height, Format, GL_UNSIGNED_SHORT, resized_image_16);
				stbi_image_free(resized_image_16);
			}
			else if (pixel_data_16) {
				glTextureSubImage2D(m_Renderid, 0, 0, 0, m_Width, m_Height, Format, GL_UNSIGNED_SHORT, pixel_data_16);
				stbi_image_free(pixel_data_16);
			}
			glBindTexture(GL_TEXTURE_2D, 0);
		}

	}

	void OpenGlTexture2D::Create8BitsTexture(const std::string& path)
	{
		GLenum InternalFormat = 0, Format = 0;

		stbi_set_flip_vertically_on_load(1);
		pixel_data_8 = stbi_load(path.c_str(), &m_Width, &m_Height, &channels, 0);

		if (pixel_data_8 == nullptr) {
			LOG_ERROR("{}{}", path, "2D Image not found!!");
			CreateWhiteTexture();
		}
		else 
		{
			if (channels == 4)
			{
				InternalFormat = GL_RGBA8;
				Format = GL_RGBA;
			}
			else if (channels == 3)
			{
				InternalFormat = GL_RGB8;
				Format = GL_RGB;
			}
			else if (channels == 2)
			{
				InternalFormat = GL_RG8;
				Format = GL_RG;
			}
			else if (channels == 1)
			{
				InternalFormat = GL_R8;
				Format = GL_RED;
			}
			else
				LOG_ERROR("Invalid Texture format");

			glCreateTextures(GL_TEXTURE_2D, 1, &m_Renderid);
			glTextureStorage2D(m_Renderid, 1, InternalFormat, m_Width, m_Height);

			glGenerateTextureMipmap(m_Renderid);
			glTextureParameteri(m_Renderid, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTextureParameteri(m_Renderid, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_NEAREST);
			glTextureParameteri(m_Renderid, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTextureParameteri(m_Renderid, GL_TEXTURE_WRAP_R, GL_REPEAT);

			if (resized_image_8)
			{
				glTextureSubImage2D(m_Renderid, 0, 0, 0, m_Width, m_Height, Format, GL_UNSIGNED_BYTE, resized_image_8);
				stbi_image_free(resized_image_8);
			}
			else if (pixel_data_8) {
				glTextureSubImage2D(m_Renderid, 0, 0, 0, m_Width, m_Height, Format, GL_UNSIGNED_BYTE, pixel_data_8);
				stbi_image_free(pixel_data_8);
			}
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}

	OpenGlTexture2D::~OpenGlTexture2D()
	{
		glDeleteTextures(1, &m_Renderid);
	}

	void OpenGlTexture2D::Bind(int slot = 0) const
	{
		glBindTextureUnit(slot, m_Renderid);
	}

	void OpenGlTexture2D::UnBind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void OpenGlTexture2D::CreateWhiteTexture()
	{
		pixel_data_8 = stbi_load("assets/textures/white.jpg", &m_Width, &m_Height, &channels, 0);
		if (pixel_data_8 == nullptr)
			LOG_ERROR("Image not found!!");
		Resize_Image(16, 16);
		glCreateTextures(GL_TEXTURE_2D, 1, &m_Renderid);
		glTextureStorage2D(m_Renderid, 1, GL_RGB8, 16, 16);

		glGenerateTextureMipmap(m_Renderid);
		glTextureParameteri(m_Renderid, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTextureParameteri(m_Renderid, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		glTextureParameteri(m_Renderid, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_Renderid, GL_TEXTURE_WRAP_R, GL_REPEAT);

		if (resized_image_8)
		{
			glTextureSubImage2D(m_Renderid, 0, 0, 0, 16, 16, GL_RGB, GL_UNSIGNED_BYTE, resized_image_8);
			stbi_image_free(resized_image_8);
		}
		else if (pixel_data_8) {
			glTextureSubImage2D(m_Renderid, 0, 0, 0, m_Width, m_Height, GL_RGB, GL_UNSIGNED_BYTE, pixel_data_8);
			stbi_image_free(pixel_data_8);
		}
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	/*
	* @brief ��������ͼ��Ĵ�С (֧�� 8 λ�� 16 λ����)
	* @param width Ŀ��ͼ����
	* @param height Ŀ��ͼ��߶�
	* @param bUse16BitTexture �Ƿ�ʹ�� 16 λ����
	*/
	void OpenGlTexture2D::Resize_Image(const float& width, const float& height, bool bUse16BitTexture)
	{
		if (bUse16BitTexture)
		{
			if (m_Height > width && m_Width > height)
			{
				resized_image_16 = new unsigned short[width * height * channels];
				stbir_resize_uint16_generic(pixel_data_16, m_Width, m_Height, 0, resized_image_16, width, height, 0, channels, 0, 0, STBIR_EDGE_REFLECT, STBIR_FILTER_BOX, STBIR_COLORSPACE_LINEAR, 0);
				m_Height = height;
				m_Width = width;
			}
		}
		else
		{
			if (m_Height > width && m_Width > height)
			{
				resized_image_8 = new unsigned char[width * height * channels];
				stbir_resize_uint8(pixel_data_8, m_Width, m_Height, 0, resized_image_8, width, height, 0, channels);

				m_Height = height;
				m_Width = width;
			}
		}
	}
}