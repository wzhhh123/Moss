

#include "mspch.h"
#include "Renderer.h"
#include "RenderCommand.h"
#include "../../Platform/OpenGL/OpenGLShader.h"

namespace Moss {


	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData();

	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{

	}

	void Renderer::Submit(const Moss::Ref<VertexArray>& vertexArray, const Moss::Ref<Shader>& shader, const glm::mat4& transform)
	{
		shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Transform",  transform);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

}
