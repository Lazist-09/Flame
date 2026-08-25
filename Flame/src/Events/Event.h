#pragma once
#include "flpch.h"
#include "Core/Core.h"





namespace Flame {

	//目前事件是阻塞的，意味着事件发生会立即处理，处理完再继续运行
	//未来可能在事件总线或者缓冲池进行异步处理

	enum class EventType {

		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled

	};

	//用于事件分类，方便事件处理器进行过滤
	enum EventCategory {

		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput = BIT(1),
		EventCategoryKeyboard = BIT(2),
		EventCategoryMouse = BIT(3),
		EventCategoryMouseButton = BIT(4)

	};

#define EventClassType(type) static EventType GetStaticType() { return EventType::##type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

#define EventClassCategory(category) virtual int GetCategoryFlags() const override { return category; }

	class FL_API Event {

		friend class EventDispatcher;
	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory category) {
			return GetCategoryFlags() & category;
		}
		bool Handled = false;

	};

	class EventDispatcher {
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	public:

		EventDispatcher(Event& event)
			: m_Event(event) {

		}

		template<typename T>
		bool Dispatch(EventFn<T> func) {

			if (m_Event.GetEventType() == T::GetStaticType()) {

				m_Event.Handled = func(*(T*)&m_Event);
				return true;

			}
			return false;

		}
	private:

		Event& m_Event;
	};

	//用于一般<<操作符重载，方便打印事件信息
	template<typename T>
	inline std::enable_if_t<std::is_base_of_v<Event, T>, std::ostream&>
		operator<<(std::ostream& os, const T& e) {
		return os << e.ToString();
	}

	//新版fmt的格式化，旧版fmt的ostream重载已经被弃用.
	inline std::string format_as(const Event& e) {
		return e.ToString();
	};
	

}

