

#include "mspch.h"
#include "Buffer.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Moss {

	Moss::VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case  RendererAPI::API::None:
			MS_CORE_ASSERT(false, "RendererAPI::None is not supported!");
			return nullptr;
		case  RendererAPI::API::OpenGL:
			return new OpenGLVertexBuffer(vertices, size);
		default:
			break;
		}
		MS_CORE_ASSERT(false, "Unknow RendererAPI!");
		return nullptr;
	}

	Moss::IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
		case  RendererAPI::API::None:
			MS_CORE_ASSERT(false, "RendererAPI::None is not supported!");
			return nullptr;
		case  RendererAPI::API::OpenGL:
			return new OpenGLIndexBuffer(indices, count);
		default:
			break;
		}
		MS_CORE_ASSERT(false, "Unknow RendererAPI!");
		return nullptr;
	}
}