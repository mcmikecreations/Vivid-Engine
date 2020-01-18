#include <GLFW/glfw3.h>
#include "vivid_core/utility/error.h"
#include "ui/windows_window.h"

using namespace vivid_core::ui;

int windows_window::init(int width, int height, const char* title)
{
	_width = width;
	_height = height;

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	_window = glfwCreateWindow(width, height, title, nullptr, nullptr);

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