#pragma once

#include "RendererAPI.h"

namespace Moss {



	class Renderer {
	public:

		static void BeginScene();
		static void EndScene();
		static void Submit(const std::shared_ptr<VertexArray>& vertexArray);


		inline static RendererAPI::API GetAPI() { return s_RendererAPI; }

	private:
		static RendererAPI::API s_RendererAPI;
	};
	
}