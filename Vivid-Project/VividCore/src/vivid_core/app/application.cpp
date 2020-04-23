#include "vivid_core/app/application.h"
#include "vivid_core/utility/error.h"

//Include for Vulkan support only
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "spdlog/async.h"
#include "spdlog/sinks/stdout_color_sinks.h" // or "../stdout_sinks.h" if no colors needed
#include "spdlog/sinks/basic_file_sink.h"

#include "vivid_core/utility/dependencies.h"

using namespace vivid_core::app;
using namespace vivid_core::utility;

int application::run()
{
	init();
	main_loop();
	term();
	return (int)error::SUCCESS;
}

int application::init()
{
	int res = (int)error::SUCCESS;
	res = init_logger();
	if (res != (int)error::SUCCESS)
	{
		term_logger();
		return res;
	}
	res = init_context();
	if (res != (int)error::SUCCESS)
	{
		term_context();
		term_logger();
		return res;
	}
	res = init_window();
	if (res != (int)error::SUCCESS)
	{
		term_window();
		term_context();
		term_logger();
		return res;
	}

	spdlog::info("Init successful");
	return (int)error::SUCCESS;
}

int application::term()
{
	term_window();
	term_context();
	term_logger();

	return (int)error::SUCCESS;
}

int application::main_loop()
{
	//TODO - put this into an event handler
	while (!glfwWindowShouldClose((GLFWwindow*)_window->expose_handle())) {
		glfwPollEvents();
	}
	return (int)error::SUCCESS;
}

int application::init_context()
{
	_context.reset(ui::ui_context::create());
	return _context->init();
}

int application::init_window()
{
	_window.reset(ui::window::create());
	return _window->init(ui::window_props());
}

int application::init_logger()
{
	//TODO - replace allocations with a custom allocator
	auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
	console_sink->set_level(spdlog::level::warn);

	auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("log.txt", true);
	file_sink->set_level(spdlog::level::trace);

	spdlog::sinks_init_list sink_list = { file_sink, console_sink };
	spdlog::logger *logger = new spdlog::logger("global log", sink_list.begin(), sink_list.end());
	logger->set_level(spdlog::level::debug);

	_logger = std::shared_ptr<spdlog::logger>(logger);
	spdlog::set_default_logger(_logger);

	return (int)error::SUCCESS;
}

int application::term_logger()
{
	spdlog::drop_all();
	spdlog::shutdown();
	return (int)error::SUCCESS;
}

int application::term_context()
{
	if (_context) return _context->term();
	return (int)error::SUCCESS;
}

int application::term_window()
{
	return (int)error::SUCCESS;
}