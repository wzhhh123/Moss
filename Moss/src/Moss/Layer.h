#pragma once

#include "Moss/Core.h"
#include "Event/Event.h"

namespace Moss {

	class MOSS_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& event) {}
		virtual void OnImGuiRender(){}

		inline const std::string& GetName()const { return m_DebugName; }

	protected:
		std::string m_DebugName;
	};

}

