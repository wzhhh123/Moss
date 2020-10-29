#pragma once

#include "glm/glm.hpp"
#include "Moss/Renderer/VertexArray.h"
#include "Moss/Renderer/RendererAPI.h"

namespace Moss {

	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		void SetClearColor(const glm::vec4& color) override;
		void Clear() override;
		void DrawIndexed(const Moss::Ref<VertexArray>&vertexArray) override;
		void Init() override;
	};


}

