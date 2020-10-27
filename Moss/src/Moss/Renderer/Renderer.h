#pragma once

#include "RendererAPI.h"
#include "OrthographicCamera.h"
#include "Shader.h"

namespace Moss {



	class Renderer {
	public:

		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();
		static void Submit(const Moss::Ref<VertexArray>& vertexArray, const Moss::Ref<Shader>& shader, const glm::mat4& transform = glm::mat4(1.0f));
		static void Init();

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* m_SceneData;
	};
	
}