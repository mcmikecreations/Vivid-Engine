#pragma once

#include <GLFW/glfw3.h>
#include "vivid_core/utility/macros.h"
#include "vivid_core/app/window_controllers/window_controller.h"

START_ENGINE
START_NAME(app)
START_NAME(window_controllers)

class glfw_window_controller : public window_controller
{
public:
	int init(int width, int height, const char* title) override;
	int term() override;
private:
	int _width, _height;
	GLFWwindow* _window;
};


END_NAME(window_controllers)
END_NAME(app)
END_ENGINE