
#include "mspch.h"
#include "Moss/Moss.h"


class ExampleLayer : public Moss::Layer {
public:
	ExampleLayer() :Layer("Example"){

	}
	void OnUpdate() override {
		MS_INFO("ExampleLayer::Update");
	}

	void OnEvent(Moss::Event& event)override {
		MS_TRACE("{0}", event);
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