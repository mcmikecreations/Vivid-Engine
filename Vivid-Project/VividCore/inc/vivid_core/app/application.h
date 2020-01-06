#pragma once

#include <memory>
#include "spdlog/spdlog.h"

#include "vivid_core/app/context.h"
#include "vivid_core/app/window.h"

namespace vivid_core
{
	namespace app
	{
		class application {
		private:
			std::shared_ptr<spdlog::logger> _logger;
			context* _context;
			window* _window;
		public:
			int run();
		private:
			int init();
			int mainLoop();
			int term();

			int initLogger();
			int initContext();
			int initWindow();

			int termLogger();
			int termContext();
			int termWindow();
		};
	}
}