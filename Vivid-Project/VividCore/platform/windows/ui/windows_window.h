#pragma once

#include <GLFW/glfw3.h>
#include "vivid_core/utility/macros.h"
#include "vivid_core/ui/window.h"

START_ENGINE
START_NAME(ui)

class windows_window : public window
{
public:
	virtual ~windows_window(){}

	virtual int init(window_props& props) override;
	virtual int term() override;
	virtual void* expose_handle() override;
private:
	GLFWwindow* _window;
	window_props _props;
};

END_NAME(ui)
END_ENGINE