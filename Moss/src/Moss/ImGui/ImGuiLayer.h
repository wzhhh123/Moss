#pragma once

#include "Moss/Core.h"
#include "Moss/Layer.h"
#include "Moss/Event/Event.h"
#include "Moss/Event/MouseEvent.h"
#include "Moss/Event/KeyEvent.h"
#include "Moss/Event/ApplicationEvent.h"
namespace Moss {

	class MOSS_API ImGuiLayer : public Layer {

	public:

		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Event& e);


	private:
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMosueMovedEvent(MosueMovedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool OnKeyTypedEvent(KeyTypedEvent& e);
		bool OnWindowResizeEvent(WindowResizeEvent& e);
	private:
		float m_Time = 0;
	};

}