
#include "mspch.h"
#include "Application.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <Moss/Input.h>

namespace Moss {

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
		switch (type)
		{
		case Moss::ShaderDataType::Float:				return GL_FLOAT;
		case Moss::ShaderDataType::Float2:			return GL_FLOAT;
		case Moss::ShaderDataType::Float3:			return GL_FLOAT;
		case Moss::ShaderDataType::Float4:			return GL_FLOAT;
		case Moss::ShaderDataType::Mat3:				return GL_FLOAT;
		case Moss::ShaderDataType::Mat4:				return GL_FLOAT;
		case Moss::ShaderDataType::Int:					return GL_INT;
		case Moss::ShaderDataType::Int2:				return GL_INT;
		case Moss::ShaderDataType::Int3:				return GL_INT;
		case Moss::ShaderDataType::Int4:				return GL_INT;
		case Moss::ShaderDataType::Bool:				return GL_BOOL;

		}
		MS_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	Application* Application::s_Instance = nullptr;

	Application::Application() {
		MS_CORE_ASSERT(!s_Instance, "Application already exits!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());

		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		float vertices[7 * 3] = {
			-0.5f,-0.5f,0.0f, 1.0f,1.0f,0.0f,0.0f,
			0.5f,-0.5f,0.0f,1.0f,1.0f,1.0f,0.0f,
			0.0f,0.5f,0.0f,0.0f,1.0f,0.0f,0.0f,
		};

		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		m_VertexBuffer->Bind();

		BufferLayout layout = {
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float4, "a_Color"},
		};


		int index = 0;
		for (auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(
				index, 
				element.GetElementComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ?  GL_TRUE : GL_FALSE,
				layout.GetStride(), (const void*)element.Offset);
			index++;
		}


		unsigned int indices[3] = {
			0,1,2
		};
		m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(unsigned int)));
		m_IndexBuffer->Bind();
		glBindVertexArray(0);

		std::string vertexSrc = R"(
			#version 330 core
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			out vec4 Color;
			void main()
			{
				Color = a_Color;
				gl_Position = vec4(a_Position,1);
			}		
		)";


		std::string fragmentSrc = R"(
			#version 330 core
			layout(location = 0) out vec4 color;
			in vec4 Color;
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
			glClearColor(0.2f, 0.2f, 0.2f, 0.2f);
			glClear(GL_COLOR_BUFFER_BIT);

			m_Shader->Bind();
			glBindVertexArray(m_VertexArray);
			glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);


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