

#include "mspch.h"
#include "Shader.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"


namespace Moss {

	Moss::Shader* Moss::Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc) 
	{
		switch (Renderer::GetAPI())
		{
		case  RendererAPI::API::None:
			MS_CORE_ASSERT(false, "RendererAPI::None is not supported!");
			return nullptr;
		case  RendererAPI::API::OpenGL:
			return new OpenGLShader(vertexSrc, fragmentSrc);
		default:
			break;
		}
		MS_CORE_ASSERT(false, "Unknow RendererAPI!");
		return nullptr;
	}

}
