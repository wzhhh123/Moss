#include "Moss/Moss.h"


class Sandbox : public Moss::Application {
public:
	Sandbox() {

	}
	~Sandbox() {

	}
};


Moss::Application* Moss::CreateApplication()
{
	return new Sandbox();
}