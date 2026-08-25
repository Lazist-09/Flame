#pragma once

#include "Event.h"



namespace Flame {

	

	class FL_API WindowResizeEvent : public Event {

	public:
		WindowResizeEvent(unsigned int width, unsigned int height)
			: m_Width(width), m_Height(height) {
		}

		inline unsigned int GetWidth() const { return m_Width; }
		inline unsigned int GetHeight() const { return m_Height; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
			return ss.str();
		}

		EventClassType(WindowResize)
		EventClassCategory(EventCategoryApplication)

	private:
		unsigned int m_Width, m_Height;
	};

	class FL_API WindowCloseEvent : public Event {

	public:
		WindowCloseEvent() = default;

		std::string ToString() const override {
			std::stringstream ss;
			ss << "WindowCloseEvent";
			return ss.str();
		}

		EventClassType(WindowClose)
		EventClassCategory(EventCategoryApplication)
	};

	class AppTickEvent : public Event
	{
	public:
		AppTickEvent() = default;

		EventClassType(AppTick)
		EventClassCategory(EventCategoryApplication)
	};

	class AppUpdateEvent : public Event
	{
	public:
		AppUpdateEvent() = default;

		EventClassType(AppUpdate)
		EventClassCategory(EventCategoryApplication)
	};

	class AppRenderEvent : public Event
	{
	public:
		AppRenderEvent() = default;

		EventClassType(AppRender)
		EventClassCategory(EventCategoryApplication)
	};
}