#pragma once

#include "vivid_core/utility/macros.h"

START_ENGINE
START_NAME(ui)

enum class ui_api
{
	None = 0,
	GLFW = 1,
};

class ui_api_wrapper
{
private:
	static ui_api _api;
public:
	inline static ui_api get_api() { return _api; }
};

END_NAME(ui)
END_ENGINE