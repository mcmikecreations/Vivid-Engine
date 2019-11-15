#include "vivid_core/app/application.h"
#include "vivid_core/utility/errors.h"

using namespace vivid_core::app;
using namespace vivid_core::utility;

int application::run()
{
	initVulkan();
	mainLoop();
	cleanup();
	return (int)errors::NONE;
}

int application::initVulkan()
{
	return (int)errors::NONE;
}

int application::cleanup()
{
	return (int)errors::NONE;
}

int application::mainLoop()
{
	return (int)errors::NONE;
}