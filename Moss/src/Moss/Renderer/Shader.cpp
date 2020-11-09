

#include "mspch.h"
#include "Shader.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"


namespace Moss {

	Moss::Ref<Shader> Moss::Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc) 
	{
		switch (Renderer::GetAPI())
		{
		case  RendererAPI::API::None:
			MS_CORE_ASSERT(false, "RendererAPI::None is not supported!");
			return nullptr;
		case  RendererAPI::API::OpenGL:
			
			return  std::make_shared<OpenGLShader>(name, vertexSrc, fragmentSrc);
		default:
			break;
		}
		MS_CORE_ASSERT(false, "Unknow RendererAPI!");
		return nullptr;
	}

	
	Moss::Ref<Shader> Shader::Create( const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
		case  RendererAPI::API::None:
			MS_CORE_ASSERT(false, "RendererAPI::None is not supported!");
			return nullptr;
		case  RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLShader>(filepath);
		default:
			break;
		}
		MS_CORE_ASSERT(false, "Unknow RendererAPI!");
		return nullptr;
	}


	void ShaderLibrary::Add(const std::string name, const Ref<Shader>& shader) {
		MS_CORE_ASSERT(!Exists(name), "Shader already exists!");
		m_Shaders[name] = shader;
	}


	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		auto& name = shader->GetName();
		Add(name, shader);
	}

	Moss::Ref<Moss::Shader> ShaderLibrary::Load(const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(shader);
		return shader;
	}

	Moss::Ref<Moss::Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(name, shader);
		return shader;
	}

	Moss::Ref<Moss::Shader> ShaderLibrary::Get(const std::string& name)
	{
		MS_CORE_ASSERT(Exists(name), "Shader not exists!");
		return m_Shaders[name];
	}

	bool ShaderLibrary::Exists(const std::string& name) const {
		return m_Shaders.find(name) != m_Shaders.end();
	}


}
