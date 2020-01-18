#include <GLFW/glfw3.h>
#include "vivid_core/utility/error.h"
#include "vivid_core/app/context_controllers/glfw_context_controller.h"
#include <iostream>

using namespace vivid_core::app::context_controllers;

int glfw_context_controller::init()
{
	if (glfwInit() == GLFW_TRUE) return (int)vivid_core::utility::error::SUCCESS;
	return (int)vivid_core::utility::error::FAILURE;
}

int glfw_context_controller::term()
{
	glfwTerminate();
	return (int)vivid_core::utility::error::SUCCESS;
}