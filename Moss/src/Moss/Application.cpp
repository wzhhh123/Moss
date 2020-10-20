
#include "mspch.h"
#include "Application.h"
#include <GLFW/glfw3.h>
#include <Moss/Input.h>
#include <Moss/Renderer/Renderer.h>
#include <Moss/Renderer/RenderCommand.h>
namespace Moss {

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	

	Application* Application::s_Instance = nullptr;

	Application::Application() : m_Camera(-1,1,-1,1){
		MS_CORE_ASSERT(!s_Instance, "Application already exits!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());

		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

	
		float vertices[7 * 3] = {
			-0.5f,-0.5f,0.0f, 1.0f,1.0f,0.0f,0.0f,
			0.5f,-0.5f,0.0f,1.0f,1.0f,1.0f,0.0f,
			0.0f,0.5f,0.0f,0.0f,1.0f,0.0f,0.0f,
		};

		std::shared_ptr<VertexBuffer>m_VertexBuffer;
		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		BufferLayout layout = {
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float4, "a_Color"},
		};
		m_VertexBuffer->SetLayout(layout);

		m_VertexArray.reset(VertexArray::Create());
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);


		unsigned int indices[3] = {
			0,1,2
		};


		std::shared_ptr<IndexBuffer> m_IndexBuffer;
		m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(unsigned int)));

		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		std::string vertexSrc = R"(
			#version 330 core
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			
			uniform mat4 u_ViewProjection;

			out vec4 Color;
			void main()
			{
				Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position,1);
				
			}		
		)";


		std::string fragmentSrc = R"(
			#version 330 core
			layout(location = 0) out vec4 color;
			in vec4 Color;
			//in vec3 v_Position;
			void main()
			{
				color = Color;
				//color = vec4(0.8,0.2,0.3,1);
			}		
		)";

		m_Shader.reset(new Shader(vertexSrc, fragmentSrc));
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

			RenderCommand::SetClearColor(glm::vec4(0.2f, 0.2f, 0.2f, 0.2f));
			RenderCommand::Clear();

			Renderer::BeginScene();

			m_Shader->Bind();
			m_Shader->UploadUniformMat4("u_ViewProjection", m_Camera.GetViewProjectionMatrix());
			Renderer::Submit(m_VertexArray);
			Renderer::EndScene();
	

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			//auto[x, y] = Input::GetMousePosition();
			//MS_CORE_TRACE("{0}, {1}", x, y);

			//放在渲染线程 begin到end
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