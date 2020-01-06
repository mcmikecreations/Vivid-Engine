#pragma once

#include "vivid_core/utility/macros.h"
#include <boost/di.hpp>

#include "vivid_core/app/context_controllers/context_controller.h"
#include "vivid_core/app/window_controllers/window_controller.h"

#include "vivid_core/app/context_controllers/glfw_context_controller.h"
#include "vivid_core/app/window_controllers/glfw_window_controller.h"

START_ENGINE
START_NAME(utility)

class dependencies
{
private:
	dependencies();
public:
	dependencies(dependencies const&) = delete;
	void operator=(dependencies const&) = delete;

	static dependencies& get_instance();
	static auto& get_injector() noexcept
	{
		return boost::di::make_injector(
			boost::di::bind<app::context_controllers::context_controller>
			.to<app::context_controllers::glfw_context_controller>()
		,	boost::di::bind<app::window_controllers::window_controller>
			.to<app::window_controllers::glfw_window_controller>()
		);
	}
};

END_NAME(utility)
END_ENGINE