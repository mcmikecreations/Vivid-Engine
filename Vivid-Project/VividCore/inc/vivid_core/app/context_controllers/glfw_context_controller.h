#pragma once

#include "vivid_core/utility/macros.h"
#include "vivid_core/app/context_controllers/context_controller.h"

START_ENGINE
START_NAME(app)
START_NAME(context_controllers)

class glfw_context_controller : context_controller
{
public:
	int init() override;
	int term() override;
};

END_NAME(context_controllers)
END_NAME(app)
END_ENGINE