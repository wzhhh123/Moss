#include "mspch.h"
#include "RenderCommand.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Moss {


	Moss::RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();

}