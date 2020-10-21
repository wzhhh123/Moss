
#include "mspch.h"
#include "Application.h"
#include <GLFW/glfw3.h>
#include <Moss/Input.h>
#include <Moss/Renderer/Renderer.h>
#include <Moss/Renderer/RenderCommand.h>
namespace Moss {

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	

	Application* Application::s_Instance = nullptr;

	Application::Application(){
		MS_CORE_ASSERT(!s_Instance, "Application already exits!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());

		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

	
	}

	Application::~Application() 
	{

	}

	void Application::OnEvent(Event& e) {

		EventDispatch dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
		//MS_CORE_TRACE("{0}", e);

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
			(*--it)->OnEvent(e);
			if (e.Handled())
				break;
		}

	}

	void Application::PushLayer(Layer* layer) {
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer) {
		m_LayerStack.PushOverlay(layer);
	}

	void Application::Run() {
		while (m_IsRunning) 
		{

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			//������Ⱦ�߳� begin��end
			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}


	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_IsRunning = false;
		return true;
	}

}