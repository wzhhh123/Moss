

#include "mspch.h"
#include "Renderer.h"
#include "RenderCommand.h"

namespace Moss {

	RendererAPI::API Moss::Renderer::s_RendererAPI = RendererAPI::API::OpenGL;

	void Renderer::BeginScene()
	{

	}

	void Renderer::EndScene()
	{

	}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray)
	{
		RenderCommand::DrawIndexed(vertexArray);
	}

}
