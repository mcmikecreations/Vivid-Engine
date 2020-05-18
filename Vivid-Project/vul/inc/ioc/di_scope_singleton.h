#pragma once

#include "ioc/di_scope.h"

namespace vul {
namespace ioc {
	/** A singleton scope to store a specific value inside.

	\tparam _Ty The type of value to be stored.
	*/
template <class _Ty>
class di_scope_singleton : public di_scope<_Ty>
{
public:
	/// Sets the initial active or inactive state
	using initial_scope = std::true_type;
	/** Construct a singleton scope with a value and additional
	parameters, that indicate state. This scope does **not**
	store a single value. IoC Container instantiates and tracks
	only a single object of this class.

	\param[in] is_scope Indicates if the current scope object
	is active.
	\param[in] value The value, constructed by the ioc
	container.
	\param[in] di A pointer to the ioc container instance, used
	for cross-referencing.
	*/
	di_scope_singleton(bool* is_scope, _Ty* value, void* di)
		: di_scope<_Ty>(is_scope, value, di) {}
	/** Indicate if this scope object is active.

	\param[in] value The value indicating if this scope is
	active.
	\returns success if the function succeeded, failure
	otherwise.
	*/
	virtual int set_scope(bool value) override
	{
		return (int)vul::error::success;
	}
};

}
}