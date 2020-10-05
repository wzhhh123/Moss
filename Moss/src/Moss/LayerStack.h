#pragma once

#include "Moss/Core.h"
#include "Moss/Layer.h"
#include <vector>
namespace Moss {

	class MOSS_API LayerStack
	{

	public:
		LayerStack();
		~LayerStack();
		
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* layer);

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }
	private:
		std::vector<Layer*>m_Layers;
		std::vector<Layer*>::iterator m_LayerInsert;
	};

}

