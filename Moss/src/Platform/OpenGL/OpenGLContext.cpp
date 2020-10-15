#include "mspch.h"
#include "OpenGLContext.h"
#include "GLFW/glfw3.h"
#include "glad/glad.h"

namespace Moss {


	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : m_windowHandle(windowHandle)
	{
		MS_CORE_ASSERT(windowHandle, "Window handle is null!");
	}

	void OpenGLContext::Init() 
	{
		glfwMakeContextCurrent(m_windowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		MS_CORE_ASSERT(status, "Failed to initialize Glad!");
		MS_CORE_INFO("OpenGL Info:");
		MS_CORE_INFO("Vendor: {0}", glGetString(GL_VENDOR));
		MS_CORE_INFO("Renderer: {0}", glGetString(GL_RENDERER));
		MS_CORE_INFO("Version: {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers() 
	{
		glfwSwapBuffers(m_windowHandle);
	}


}