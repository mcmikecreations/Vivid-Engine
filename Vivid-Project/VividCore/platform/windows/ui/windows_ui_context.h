#pragma once

#include <GLFW/glfw3.h>
#include "vivid_core/utility/macros.h"
#include "vivid_core/ui/ui_context.h"

START_ENGINE
START_NAME(ui)

class windows_ui_context : public ui_context
{
public:
	virtual ~windows_ui_context() {}

	virtual int init() override;
	virtual int term() override;
};

END_NAME(ui)
END_ENGINE