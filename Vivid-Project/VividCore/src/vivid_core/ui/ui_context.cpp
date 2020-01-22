#include "vivid_core/ui/ui_context.h"
#include "vivid_core/ui/ui_api.h"

#ifdef VV_GLFW
#include "ui/windows_ui_context.h"
#endif

using namespace vivid_core::ui;

ui_context* ui_context::create()
{
	auto api = ui_api_wrapper::get_api();
	switch (api)
	{
	case vivid_core::ui::ui_api::None:
		VV_CORE_ASSERT(false, "No mock ui api exists.");
		return nullptr;
#ifdef VV_GLFW
	case vivid_core::ui::ui_api::GLFW:
		return new windows_ui_context();
#endif
	default:
		VV_CORE_ASSERT(false, "No ui api specified.");
		return nullptr;
	}
}