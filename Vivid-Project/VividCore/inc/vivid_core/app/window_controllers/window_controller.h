#pragma once

#include "vivid_core/utility/macros.h"

START_ENGINE
START_NAME(app)
START_NAME(window_controllers)

class window_controller
{
public:
	virtual int init(int width, int height, const char* title)=0;
	virtual int term()=0;
};

END_NAME(window_controllers)
END_NAME(app)
END_ENGINE