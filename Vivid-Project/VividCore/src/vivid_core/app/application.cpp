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
	mainLoop();
	term();
	auto &a = dependencies::get_instance();
	return (int)error::SUCCESS;
}

int application::init()
{
	int res = (int)error::SUCCESS;
	res = initLogger();
	if (res != (int)error::SUCCESS)
	{
		termLogger();
		return res;
	}
	res = initContext();
	if (res != (int)error::SUCCESS)
	{
		termContext();
		termLogger();
		return res;
	}
	res = initWindow();
	if (res != (int)error::SUCCESS)
	{
		termWindow();
		termContext();
		termLogger();
		return res;
	}

	_logger->info("Init successful");
	return (int)error::SUCCESS;
}

int application::term()
{
	termWindow();
	termContext();
	termLogger();

	return (int)error::SUCCESS;
}

int application::mainLoop()
{
	return (int)error::SUCCESS;
}

int application::initContext()
{

	return (int)error::SUCCESS;
}

int application::initWindow()
{
	return (int)error::SUCCESS;
}

int application::initLogger()
{
	auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
	console_sink->set_level(spdlog::level::warn);
	//console_sink->set_pattern("[multi_sink_example] [%^%l%$] %v");

	auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("log.txt", true);
	file_sink->set_level(spdlog::level::trace);

	spdlog::sinks_init_list sink_list = { file_sink, console_sink };
	//TODO - replace this new with a custom allocator
	spdlog::logger *logger = new spdlog::logger("global log", sink_list.begin(), sink_list.end());
	logger->set_level(spdlog::level::debug);

	_logger = std::shared_ptr<spdlog::logger>(logger);

	return (int)error::SUCCESS;
}

int application::termLogger()
{
	spdlog::drop_all();
	spdlog::shutdown();
	return (int)error::SUCCESS;
}

int application::termContext()
{
	return (int)error::SUCCESS;
}

int application::termWindow()
{
	return (int)error::SUCCESS;
}