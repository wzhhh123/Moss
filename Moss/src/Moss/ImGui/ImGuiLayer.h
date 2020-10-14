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

		//virtual可写可不写 override也是，全写比较清楚
		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();

	private:
		float m_Time = 0;
	};

}