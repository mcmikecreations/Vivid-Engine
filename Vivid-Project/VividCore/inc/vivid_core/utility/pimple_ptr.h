#pragma once

#include "vividcore_export.h"

namespace VividCore
{
	namespace Utility
	{
		template <typename T>
		class VIVIDCORE_EXPORT PimplePtr {
			T * p;
		public:
			explicit PimplePtr(T * t) : p(t) {}

			const T & operator*() const { return *p; }
			T & operator*() { return *p; }

			const T * operator->() const { return p; }
			T * operator->() { return p; }
		};
	}
}