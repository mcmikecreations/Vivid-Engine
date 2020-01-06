#include "vivid_core/app/context.h"

using namespace vivid_core::app;

context::context(context_controllers::context_controller& controller) : _controller(controller){}

context::~context(){}

int context::init() { return _controller.init(); }

int context::term() { return _controller.term(); }