#include "vivid_core/utility/dependencies.h"

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