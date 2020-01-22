#include <GLFW/glfw3.h>
#include "vivid_core/utility/error.h"
#include "ui/windows_window.h"

using namespace vivid_core::ui;

int windows_window::init(window_props& props)
{
	_props._width = props._width;
	_props._height = props._height;
	_props._title = props._title;

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	_window = glfwCreateWindow(props._width, props._height, props._title, nullptr, nullptr);

	if (_window != NULL) return (int)vivid_core::utility::error::SUCCESS;
	return (int)vivid_core::utility::error::BAD_ALLOC;
}

int windows_window::term()
{
	if (_window != NULL) glfwDestroyWindow(_window);
	return (int)vivid_core::utility::error::SUCCESS;
}

void* windows_window::expose_handle()
{
	return _window;
}