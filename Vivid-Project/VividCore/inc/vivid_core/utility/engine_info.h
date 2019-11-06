#pragma once

#include <sstream>

namespace vivid_core
{
	namespace utility
	{
		class engine_info
		{
		public:
			int GetMajor() const;
			int GetMinor() const;
			int GetPatch() const;
			const char * GetVersion() const;
		};
	}
}