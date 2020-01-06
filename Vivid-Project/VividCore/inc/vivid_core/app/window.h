#pragma once

#include "vivid_core/utility/macros.h"
#include "vivid_core/app/window_controllers/window_controller.h"

START_ENGINE
START_NAME(app)

class window
{
public:
	window(window_controllers::window_controller& controller);
	~window();

	int init(int width, int height, const char* title);
	int term();
	void* expose_handle();
private:
	window_controllers::window_controller& _controller;
};

END_NAME(app)
END_ENGINE