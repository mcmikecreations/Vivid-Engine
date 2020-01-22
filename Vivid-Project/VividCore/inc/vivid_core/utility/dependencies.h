#pragma once

#include "vivid_core/utility/macros.h"
#include <boost/di.hpp>

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
		const auto injector = boost::di::make_injector(
			//boost::di::bind<app::context_controllers::context_controller>
			//.to<app::context_controllers::glfw_context_controller>()
		);
		return injector;
	}
};

END_NAME(utility)
END_ENGINE