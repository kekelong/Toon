#include "runtime/function/render/opengl/interface/rhi_texture.h"
#include "runtime/function/render/opengl/opengl_texture.h"
#include <stb_image.h>

namespace Toon
{
	std::shared_ptr<Texture2D> Texture2D::Create(const TextureSpecification& specification)
	{
		return std::make_shared<OpenGLTexture2D>(specification);
	}

	std::shared_ptr<Texture2D> Texture2D::Create(const std::string& path)
	{
		return std::make_shared<OpenGLTexture2D>(path);
	}
}