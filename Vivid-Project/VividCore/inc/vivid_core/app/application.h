#pragma once

#include <memory>
#include "spdlog/spdlog.h"

#include "vivid_core/app/context.h"
#include "vivid_core/ui/window.h"

namespace vivid_core
{
	namespace app
	{
		class application {
		private:
			std::shared_ptr<spdlog::logger> _logger;
			std::shared_ptr<context> _context;
			std::shared_ptr<ui::window> _window;
		public:
			int run();
		private:
			int init();
			int main_loop();
			int term();

			int init_logger();
			int init_context();
			int init_window();

			int term_logger();
			int term_context();
			int term_window();
		};
	}
}