#include "runtime/function/render/opengl/interface/rhi_framebuffer.h"
#include "runtime/function/render/opengl/opengl_framebuffer.h"

namespace Toon
{
	std::shared_ptr<FrameBuffer> FrameBuffer::Create(const FrameBufferSpecification& spec)
	{
		return std::make_shared<OpenGLFramebuffer>(spec);
	}
   
}