#include "vivid_core/utility/engine_info.h"
#include <sstream>

using namespace VividCore::Utility;

#define FILL_VERSION(major,minor,patch) \
int engine_info::GetMajor() const { return major; } \
int engine_info::GetMinor() const { return minor; } \
int engine_info::GetPatch() const { return patch; } \
const char * engine_info::GetVersion() const { return #major "." #minor "." #patch ; }

FILL_VERSION(0,0,1)

#undef FILL_VERSION