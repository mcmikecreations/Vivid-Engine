#include <GLFW/glfw3.h>
#include "vivid_core/utility/error.h"
#include "vivid_core/app/window_controllers/glfw_window_controller.h"

using namespace vivid_core::app::window_controllers;

int glfw_window_controller::init(int width, int height, const char* title)
{
	_width = width;
	_height = height;

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	_window = glfwCreateWindow(width, height, title, nullptr, nullptr);

	if (_window) return (int)vivid_core::utility::error::SUCCESS;
	return (int)vivid_core::utility::error::BAD_ALLOC;
}

int glfw_window_controller::term()
{
	if (_window) glfwDestroyWindow(_window);
	return (int)vivid_core::utility::error::SUCCESS;
}