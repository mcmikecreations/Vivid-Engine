#pragma once

#include <sstream>

namespace VividCore
{
	namespace Utility
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