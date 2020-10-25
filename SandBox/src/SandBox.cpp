
#include "mspch.h"
#include "Moss/Moss.h"
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include "imgui/imgui.h"
#include <memory>
#include "Platform/OpenGL/OpenGLShader.h"

class ExampleLayer : public Moss::Layer {
public:


	ExampleLayer() :Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f) , m_CameraPosition(0,0,0), m_Transofrm(0.0f){

		float vertices[7 * 3] = {
			-0.5f,-0.5f,0.0f, 1.0f,1.0f,0.0f,0.0f,
			0.5f,-0.5f,0.0f,1.0f,1.0f,1.0f,0.0f,
			0.0f,0.5f,0.0f,0.0f,1.0f,0.0f,0.0f,
		};

		std::shared_ptr<Moss::VertexBuffer>m_VertexBuffer;
		m_VertexBuffer.reset(Moss::VertexBuffer::Create(vertices, sizeof(vertices)));
		Moss::BufferLayout layout = {
			{Moss::ShaderDataType::Float3, "a_Position"},
			{Moss::ShaderDataType::Float4, "a_Color"},
		};
		m_VertexBuffer->SetLayout(layout);

		m_VertexArray.reset(Moss::VertexArray::Create());
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);


		unsigned int indices[3] = {
			0,1,2
		};


		std::shared_ptr<Moss::IndexBuffer> m_IndexBuffer;
		m_IndexBuffer.reset(Moss::IndexBuffer::Create(indices, sizeof(indices) / sizeof(unsigned int)));

		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		std::string vertexSrc = R"(
			#version 330 core
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			
			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;
			out vec4 Color;
			void main()
			{
				Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position,1);
				
			}		
		)";


		std::string fragmentSrc = R"(
			#version 330 core
			layout(location = 0) out vec4 color;
			in vec4 Color;

			uniform vec4 u_Color;
			void main()
			{
				color = u_Color;
				//color = vec4(0.8,0.2,0.3,1);
			}		
		)";

		m_Shader.reset(Moss::Shader::Create(vertexSrc, fragmentSrc));
	}

	void OnUpdate(Moss::Timestep ts) override {

		if (Moss::Input::IsKeyPressed(MS_KEY_LEFT))
			m_CameraPosition.x -= m_CameraSpeed * ts;
		if (Moss::Input::IsKeyPressed(MS_KEY_RIGHT))
			m_CameraPosition.x += m_CameraSpeed * ts;
		if (Moss::Input::IsKeyPressed(MS_KEY_UP))
			m_CameraPosition.y += m_CameraSpeed * ts;
		if (Moss::Input::IsKeyPressed(MS_KEY_DOWN))
			m_CameraPosition.y -= m_CameraSpeed * ts;


		if (Moss::Input::IsKeyPressed(MS_KEY_L))
			m_Transofrm.x -= m_CameraSpeed * ts;
		if (Moss::Input::IsKeyPressed(MS_KEY_R))
			m_Transofrm.x += m_CameraSpeed * ts;

	
		Moss::RenderCommand::SetClearColor(glm::vec4(0.2f, 0.2f, 0.2f, 0.2f));
		Moss::RenderCommand::Clear();


		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(0);

		Moss::Renderer::BeginScene(m_Camera);


		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Transofrm);

		std::dynamic_pointer_cast<Moss::OpenGLShader>(m_Shader)->UploadUniformFloat4("u_Color", { 0,1,0,1 });
		Moss::Renderer::Submit(m_VertexArray, m_Shader, transform);


		Moss::Renderer::EndScene();

	}

	void OnImGuiRender() override {

	}

	void OnEvent(Moss::Event& event)override {

		Moss::EventDispatch dispatcher(event);
		dispatcher.Dispatch<Moss::KeyPressedEvent>(MS_BIND_EVENT_FN(ExampleLayer::OnKeyPressedEvent));
	}

	bool OnKeyPressedEvent(Moss::KeyPressedEvent& event) {

		/*switch (event.GetKeyCode())
		{
		case MS_KEY_LEFT:
			m_CameraPosition.x -= m_CameraSpeed;
				break;
		case MS_KEY_RIGHT:
			m_CameraPosition.x += m_CameraSpeed;
			break;
		case MS_KEY_UP:
			m_CameraPosition.y += m_CameraSpeed;
			break;
		case MS_KEY_DOWN:
			m_CameraPosition.y -= m_CameraSpeed;
			break;
		default:
			break;
		}*/
		return false;
	}


private:
	std::shared_ptr<Moss::VertexArray>m_VertexArray;
	std::shared_ptr<Moss::Shader> m_Shader;
	Moss::OrthographicCamera m_Camera;

	float m_CameraSpeed = 0.1f;
	glm::vec3 m_CameraPosition;

	glm::vec3 m_Transofrm;
};

class Sandbox : public Moss::Application {
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
	}
	~Sandbox() {

	}
};


Moss::Application* Moss::CreateApplication()
{
	return new Sandbox();
}