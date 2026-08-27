#include "flpch.h"
#include "LayerStack.h"

namespace Flame
{
	LayerStack::LayerStack()
	{
		m_LayerInsert = m_Layers.begin();
	}
	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_Layers)
			delete layer;
	}
	void LayerStack::PushLayer(Layer* layer)
	{
		m_LayerInsert = m_Layers.emplace(m_LayerInsert, layer);
		layer->OnAttach();
	}
	void LayerStack::PushOverlay(Layer* overlay)
	{
		m_Layers.emplace_back(overlay);
		overlay->OnAttach();
	}

	//allow layers to rejoin in the stack,so they wont be deleted when they are popped from the stack
	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.end())
		{
			//layer->OnDetach();
			m_Layers.erase(it);
			m_LayerInsert--;
		}
	}
	void LayerStack::PopOverlay(Layer* overlay)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
		if (it != m_Layers.end())
		{
			//overlay->OnDetach();
			m_Layers.erase(it);
		}
	}
}
