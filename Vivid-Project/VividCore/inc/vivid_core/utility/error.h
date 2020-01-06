/*! @file
	@brief File containing error codes used by the engine.
*/
#pragma once

namespace vivid_core
{
	namespace utility
	{
		/*!
		@brief An enumeration of all errors, that can be returned by the engine.
		*/
		enum class error : int
		{
			/*!
			Operation was successful.
			*/
			SUCCESS = 0,
			/*!
			Operation failed.
			*/
			FAILURE = 0,
			/*!
			Memory, used by the engine, was corrupted.
			*/
			MEMORY_CORRUPT,
			/*!
			Failed to allocate memory.
			*/
			BAD_ALLOC,
			/*!
			Failed to find an object.
			*/
			OBJECT_NOT_FOUND,
		};
	}
}