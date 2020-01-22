#include <GLFW/glfw3.h>
#include "vivid_core/utility/error.h"
#include "ui/windows_ui_context.h"

using namespace vivid_core::ui;

int windows_ui_context::init()
{
	if (glfwInit() == GLFW_TRUE) return (int)vivid_core::utility::error::SUCCESS;
	return (int)vivid_core::utility::error::FAILURE;
}

int windows_ui_context::term()
{
	glfwTerminate();
	return (int)vivid_core::utility::error::SUCCESS;
}