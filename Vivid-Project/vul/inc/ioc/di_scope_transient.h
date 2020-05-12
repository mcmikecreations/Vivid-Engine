#pragma once

#include "ioc/di_scope.h"

namespace vul {
namespace ioc {
/** A transient scope to store a specific value inside.

\tparam _Ty The type of value to be stored.
*/
template <class _Ty>
class di_scope_transient : public di_scope<_Ty>
{
public:
	/// Sets the initial active or inactive state
	using initial_scope = std::true_type;
	/** Construct a transient scope with a value and additional
	parameters, that indicate state. Each transient scope,
	returned from IoC Container, should be different.

	\param[in] is_scope Indicates if the current scope object
	is active.
	\param[in] value The value, constructed by the IoC
	Container.
	\param[in] di A pointer to the IoC Container instance, used
	for cross-referencing.
	*/
	di_scope_transient(bool* is_scope, _Ty* value, void* di)
		: di_scope<_Ty>(is_scope, value, di) {}
	/// Get the poiner to the stored object in a specific type.
	virtual _Ty* get() override
	{
		//Try to return the value disregarding the scope state.
		//TODO - check if this is actually needed.
		return static_cast<_Ty*>(this->_value);
	}
};

}
}