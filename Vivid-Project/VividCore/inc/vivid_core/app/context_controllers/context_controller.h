#pragma once

#include "vivid_core/utility/macros.h"

START_ENGINE
START_NAME(app)
START_NAME(context_controllers)

class context_controller
{
public:
	virtual int init()=0;
	virtual int term()=0;
};

END_NAME(context_controllers)
END_NAME(app)
END_ENGINE