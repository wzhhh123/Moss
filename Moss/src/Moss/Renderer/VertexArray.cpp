#include "mspch.h"
#include "VertexArray.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"
#include "Moss/Renderer/Renderer.h"

namespace Moss {

	Moss::VertexArray::~VertexArray()
	{

	}
// 
// 	void Moss::VertexArray::Bind() const
// 	{
// 
// 	}
// 
// 	void Moss::VertexArray::Unbind() const
// 	{
// 
// 	}
// 
// 	void Moss::VertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
// 	{
// 
// 	}
// 
// 	void Moss::VertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
// 	{
// 
// 	}

	Moss::VertexArray* Moss::VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case  RendererAPI::None:
			MS_CORE_ASSERT(false, "RendererAPI::None is not supported!");
			return nullptr;
		case  RendererAPI::OpenGL:
			return new OpenGLVertexArray();
		default:
			break;
		}
		MS_CORE_ASSERT(false, "Unknow RendererAPI!");
		return nullptr;
	}

}
