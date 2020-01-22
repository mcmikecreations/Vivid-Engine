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

	virtual int init(int width, int height, const char* title) override;
	virtual int term() override;
	virtual void* expose_handle() override;
private:
	GLFWwindow* _window;
	int _width, _height;
};

END_NAME(ui)
END_ENGINE