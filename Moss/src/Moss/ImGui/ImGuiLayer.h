#pragma once

#include "Moss/Core.h"
#include "Moss/Layer.h"

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
		float m_Time = 0;
	};

}