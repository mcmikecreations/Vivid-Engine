#pragma once

#include "vivid_core/utility/macros.h"

START_ENGINE
START_NAME(ui)

struct window_props
{
	unsigned int _width;
	unsigned int _height;
	const char* _title;
	
	window_props(
		const char* title = "Vivid Game", 
		unsigned int width = 640, 
		unsigned int height = 480)
		: _title(title), _width(width), _height(height) {}
};

class window
{
public:
	virtual ~window(){}

	virtual int init(window_props& props) = 0;
	virtual int term() = 0;
	virtual void* expose_handle() = 0;

	static window* create();
};

END_NAME(ui)
END_ENGINE