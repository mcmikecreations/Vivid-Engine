#include "vivid_core/ui/window.h"
#include "vivid_core/ui/ui_api.h"

#ifdef VV_GLFW
#include "ui/windows_window.h"
#endif

using namespace vivid_core::ui;

window* window::create()
{
	auto api = ui_api_wrapper::get_api();
	switch (api)
	{
	case vivid_core::ui::ui_api::None:
		VV_CORE_ASSERT(false, "No mock window api exists.");
		return nullptr;
#ifdef VV_GLFW
	case vivid_core::ui::ui_api::GLFW:
		return new windows_window();
#endif
	default:
		VV_CORE_ASSERT(false, "No window api specified.");
		return nullptr;
	}
}