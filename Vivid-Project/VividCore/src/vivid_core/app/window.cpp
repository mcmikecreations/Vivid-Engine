#include "vivid_core/app/window.h"

using namespace vivid_core::app;

window::window(window_controllers::window_controller& controller) : _controller(controller){}

window::~window(){}

int window::init(int width, int height, const char* title) { return _controller.init(width, height, title); }

int window::term() { return _controller.term(); }

void* window::expose_handle() { return _controller.expose_handle(); }