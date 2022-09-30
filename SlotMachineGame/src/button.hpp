#pragma once
#include <event.hpp>
#include <engine/engine.h>
namespace oct
{
	class button_click_event : public oct::event
	{

	};
	class button
	{
	public:
		event_handler<button_click_event> on_click;
	};
}