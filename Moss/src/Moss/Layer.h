#pragma once

#include "Moss/Core.h"
#include "Event/Event.h"
#include "Moss/Core/Timestep.h"

namespace Moss {

	class MOSS_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnImGuiRender() {}
		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName()const { return m_DebugName; }

	protected:
		std::string m_DebugName;
	};

}

