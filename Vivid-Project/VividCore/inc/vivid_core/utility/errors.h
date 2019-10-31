#pragma once

namespace VividCore
{
	namespace Utility
	{
		enum class Errors : int
		{
			NONE = 0,
			MEMORY_CORRUPT,
			BAD_ALLOC,
			OBJECT_NOT_FOUND,
		};
	}
}