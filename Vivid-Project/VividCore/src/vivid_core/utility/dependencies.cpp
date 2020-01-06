#include "vivid_core/utility/dependencies.h"

#include "vivid_core/app/context_controllers/context_controller.h"

using namespace vivid_core::utility;
namespace di = boost::di;

dependencies::dependencies()
{

}

dependencies& dependencies::get_instance()
{
	static dependencies instance;
	return instance;
}