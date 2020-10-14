
#include "mspch.h"
#include "Moss/Moss.h"
#include "glm/glm.hpp"


class ExampleLayer : public Moss::Layer {
public:
	ExampleLayer() :Layer("Example"){
	}
	void OnUpdate() override {
		//MS_INFO("ExampleLayer::Update");

		if (Moss::Input::IsKeyPressed(MS_KEY_TAB)) {
			MS_INFO("Tab key is pressed! (poll)");
		}

	}


	void OnEvent(Moss::Event& event)override {

		if (event.GetEventType() == Moss::EventType::KeyPressed) {
			Moss::KeyPressedEvent& e = (Moss::KeyPressedEvent&)event;
			if (e.GetKeyCode() == MS_KEY_TAB) {
				MS_INFO("Tab key is pressed! (event)");
			}
		}
	}
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