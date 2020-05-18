#pragma once

#include "errors.h"

namespace vul {
namespace ioc {
/** A basic scope class, holding the value, generated by the IoC
Container. It shouldn't be constructed by itself. Use the
inherited classes.
*/
class di_basic_scope
{
protected:
	bool* _is_scope;
	void* _value;
	//Allow di only to free only its own resources
	void* _di;
public:
	di_basic_scope() = delete;
	di_basic_scope(di_basic_scope&&) = delete;
	di_basic_scope(const di_basic_scope&) = delete;
	/** Construct a basic scope with a value and additional
	parameters, that indicate state.

	\param[in] is_scope Indicates if the current scope object
	is active.
	\param[in] value The value, constructed by the IoC
	Container.
	\param[in] di A pointer to the IoC Container instance, used
	for cross-referencing.
	*/
	di_basic_scope(bool* is_scope, void* value, void* di)
		: _is_scope(is_scope), _value(value), _di(di) {}
	/** A virtual destructor to ensure correct destruction of
	descendants.
	*/
	virtual ~di_basic_scope() {}
	/** Put a new value inside the scope. Disregards the old
	value and **breaks automatic memory management**.

	The value, cleared by the automatic memory manager, will be
	the original, not the replacement. In order to use this
	function, the user has to manually deallocate the
	replacement value.

	\param[in] value The replacement value for the scope object.
	\exception error::di_value_error there already is a value.
	\returns success if the replacement succeeded, error
	otherwise.
	*/
	int put(void* value)
	{
		if (_value != nullptr) return (int)vul::error::di_value_error;
		_value = value;
		return (int)vul::error::success;
	}
	/** Clear the value inside the scope. Sets the stored value
	to `nullptr`. Disregards the old value and
	**breaks automatic memory management**.

	The value, cleared by the automatic memory manager, will be
	the old value, disregarding this clear procedure. In order
	to use this function, the user has to manually deallocate
	the replacement value.

	\exception error::di_value_error there is no value.
	\returns success if the replacement succeeded, error
	otherwise.
	*/
	int clear()
	{
		if (_value == nullptr) 
			return (int)vul::error::di_value_error;
		_value = nullptr;
		return (int)vul::error::success;
	}
	/** Indicate if this scope object is active.

	\param[in] value The value indicating if this scope is
	active.
	\returns success if the function succeeded, failure
	otherwise.
	*/
	virtual int set_scope(bool value)
	{
		if (_is_scope == nullptr)
			return (int)vul::error::failure;
		*_is_scope = value;
		return (int)vul::error::success;
	}
	/// Check if this scope object is active.
	virtual bool is_scope()
	{
		return *_is_scope;
	}
	/// Get the stored value pointer.
	void* ptr()
	{
		return _value;
	}
	/// Get the stored value pointer.
	const void* ptr() const
	{
		return _value;
	}
	/// Get the stored di context.
	void* di()
	{
		return _di;
	}
	/// Get the stored di context.
	const void* di() const
	{
		return _di;
	}
};

}
}