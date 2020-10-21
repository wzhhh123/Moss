
#include "mspch.h"
#include "Moss/Moss.h"
#include "glm/glm.hpp"

#include "imgui/imgui.h"

class ExampleLayer : public Moss::Layer {
public:


	ExampleLayer() :Layer("Example"), m_Camera(-1.6, 1.6, -0.9, 0.9) {

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

		m_Shader.reset(new Moss::Shader(vertexSrc, fragmentSrc));

	}

	void OnUpdate() override {

		Moss::RenderCommand::SetClearColor(glm::vec4(0.2f, 0.2f, 0.2f, 0.2f));
		Moss::RenderCommand::Clear();


		m_Camera.SetPosition({ 0.5,0.5,0.5 });
		m_Camera.SetRotation(45);

		Moss::Renderer::BeginScene(m_Camera);
		Moss::Renderer::Submit(m_VertexArray, m_Shader);
		Moss::Renderer::EndScene();

	}

	void OnImGuiRender() override {

	}

	void OnEvent(Moss::Event& event)override {




		/*if (event.GetEventType() == Moss::EventType::KeyPressed) {
			Moss::KeyPressedEvent& e = (Moss::KeyPressedEvent&)event;
			if (e.GetKeyCode() == MS_KEY_TAB) {
				MS_INFO("Tab key is pressed! (event)");
			}
		}*/
	}


private:
	std::shared_ptr<Moss::VertexArray>m_VertexArray;
	std::shared_ptr<Moss::Shader> m_Shader;
	Moss::OrthographicCamera m_Camera;

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