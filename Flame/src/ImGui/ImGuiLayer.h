#pragma once

#include "Layer.h"

#include <memory>

namespace Flame
{
	class Framebuffer;
}

namespace Flame {

	class FL_API ImGuiLayer : public Layer {

	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		//Hope Layers can render ownly
		void Begin();
		void End();

	private:
		void SetupDockLayout();

		float m_Time = 0.0f;
		std::unique_ptr<Framebuffer> m_Framebuffer;
		float m_ViewportWidth = 0.0f;
		float m_ViewportHeight = 0.0f;
		float m_ViewportDpiScale = 0.0f;
	};

}