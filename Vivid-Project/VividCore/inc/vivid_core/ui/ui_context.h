#pragma once

#include "vivid_core/utility/macros.h"

START_ENGINE
START_NAME(ui)

class ui_context
{
public:
	virtual ~ui_context() {}

	virtual int init() = 0;
	virtual int term() = 0;

	static ui_context* create();
};

END_NAME(ui)
END_ENGINE