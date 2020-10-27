#include "mspch.h"
#include "Texture.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture2D.h"


namespace Moss {



	Moss::Ref<Moss::Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case  RendererAPI::API::None:
			MS_CORE_ASSERT(false, "RendererAPI::None is not supported!");
			return nullptr;
		case  RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLTexture2D>(path);
		default:
			break;
		}
		MS_CORE_ASSERT(false, "Unknow RendererAPI!");
		return nullptr;
	}

}