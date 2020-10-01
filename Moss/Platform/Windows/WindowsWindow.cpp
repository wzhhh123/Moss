#include "mspch.h"
#include "WindowsWindow.h"

namespace Moss {

	static bool s_GLFWInitialized = false;

	Window* Window::Create(const WindowProps& props) {
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props) {
		Init(props);
	}

	WindowsWindow::~WindowsWindow(){
		Shutdown();
	}
	
	void WindowsWindow::Init(const WindowProps& props) {
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		MS_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

		if (!s_GLFWInitialized) {
			int success = glfwInit();
			MS_CORE_ASSERT(success, "Could not initialize GLFW");
			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, props.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data); //�������m_Data��glfw�лص�������ʱ����������Ϊ����
		SetVSync(true);
	}

	void WindowsWindow::Shutdown() {
		glfwDestroyWindow(m_Window);
	}


	void WindowsWindow::OnUpdate() {
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void WindowsWindow::SetVSync(bool enabled) {
		//1����0
		glfwSwapInterval(enabled);
		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const 
	{
		return m_Data.VSync;
	}

}
