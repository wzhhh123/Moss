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

		virtual void OnAttach();
		virtual void OnDetach();
		virtual void OnUpdate();

		void Begin();
		void End();

	private:
		float m_Time = 0;
	};

}