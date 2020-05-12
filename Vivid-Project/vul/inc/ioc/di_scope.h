#pragma once

#include <type_traits>

#include "ioc/di_basic_scope.h"

namespace vul {
namespace ioc {
/** A templated scope to store a specific value inside.

\tparam _Ty The type of value to be stored.
*/
template <class _Ty>
class di_scope : public di_basic_scope
{
public:
	/// Sets the initial active or inactive state
	using initial_scope = std::true_type;
	/** Construct a templated scope with a value and additional
	parameters, that indicate state.

	\param[in] is_scope Indicates if the current scope object
	is active.
	\param[in] value The value, constructed by the IoC
	Container.
	\param[in] di A pointer to the IoC Container instance, used
	for cross-referencing.
	*/
	di_scope(bool* is_scope, _Ty* value, void* di)
		: di_basic_scope(is_scope, value, di) {}
	/// Get the poiner to the stored object in a specific type.
	virtual _Ty* get()
	{
		if (is_scope()) [[likely]]
			return static_cast<_Ty*>(_value);
		else [[unlikely]]
			return nullptr;
	}
};

}
}