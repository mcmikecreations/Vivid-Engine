#pragma once

namespace vivid_core
{
	namespace utility
	{
		enum class errors : int
		{
			NONE = 0,
			MEMORY_CORRUPT,
			BAD_ALLOC,
			OBJECT_NOT_FOUND,
		};
	}
}