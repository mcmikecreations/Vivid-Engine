#pragma once

#include "vividcore_export.h"

namespace vivid_core
{
	namespace utility
	{
		template <typename T>
		class pimple_ptr {
			T * p;
		public:
			explicit pimple_ptr(T * t) : p(t) {}

			const T & operator*() const { return *p; }
			T & operator*() { return *p; }

			const T * operator->() const { return p; }
			T * operator->() { return p; }
		};
	}
}