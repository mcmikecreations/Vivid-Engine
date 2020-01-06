#pragma once

#include "vivid_core/utility/macros.h"
#include "vivid_core/app/context_controllers/context_controller.h"

START_ENGINE
START_NAME(app)

class context
{
public:
	context(context_controllers::context_controller&);
	~context();

	int init()
	{
		return _controller.init();
	}
	int term()
	{
		return _controller.term();
	}
private:
	context_controllers::context_controller& _controller;
};

END_NAME(app)
END_ENGINE