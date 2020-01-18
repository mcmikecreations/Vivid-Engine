#pragma once

#include "vivid_core/utility/macros.h"

START_ENGINE
START_NAME(ui)

class window
{
public:
	virtual ~window(){}

	virtual int init(int width, int height, const char* title) = 0;
	virtual int term() = 0;
	virtual void* expose_handle() = 0;

	static window* create();
};

END_NAME(ui)
END_ENGINE