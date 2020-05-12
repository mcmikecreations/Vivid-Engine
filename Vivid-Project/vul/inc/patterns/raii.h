#pragma once

#include <utility>
#include <type_traits>

namespace vul {
namespace patterns {
/// A dummy structure to indicate an empty initializer in raii.
struct raii_dummy {};
/** \brief A class that implements the RAII technique / pattern
	for use inside the library.

This class manages an instance of any type, that supports
initialization and termination routines. Initialization can take
any arguments, while termination needs to be parameter-less.

In general, this class can be used as a wrapper around a
variable that requires proper initialization and termination and
you don't want to forget to call these routines.

\tparam _Ty The type of the value reference, stored inside the
raii object.
*/
template<class _Ty>
class raii
{
private:
	_Ty& _value;
	int _init;
	template <class _F, class ..._Other>
	struct first_type
	{
		using type = _F;
	};
public:
	raii() = delete;
	raii(const raii&) = delete;
	/** Construct the object, using an existing reference. This
	constructor has no guarantees of moving the reference inside
	the raii object.

	\param[in] value The value to wrap around with the raii
	object.
	*/
	raii(_Ty&& value) : _value(value), _init(0)
	{ }
	/** Construct the object, using an existing reference. Than
	initialize this reference using the supplied arguments.

	\tparam Args The argument types, passed to initialize the
	stored value.
	\param[in] args The arguments, passed to initialize the
	stored value. If args is only a raii_dummy, the value is
	initialized with an parameter-less initialization routine.
	*/
	template <class ...Args>
	raii(_Ty&& value, Args... args) : _value(value)
	{
		if constexpr (sizeof...(Args) == (std::size_t)1 && std::is_same<first_type<Args...>::type, raii_dummy>::value)
		{
			_init = _value.init();
		}
		else
		{
			_init = _value.init(std::forward<Args>(args)...);
		}
	}
	/// Calls termination routine of the stored value.
	~raii()
	{
		if (_init) _value.term();
	}
	/** Call the initialization routine of the stored reference
	using the supplied arguments.

	\tparam Args The argument types, passed to initialize the
	stored value.
	\param[in] args The arguments, passed to initialize the
	stored value. If no args are specified, the parameter-less
	version is called.
	\returns 1 if the stored value was initialized, 0 otherwise.
	*/
	template <class ...Args>
	int init(Args... args)
	{
		if (_init) return 0;
		return _init = _value.init(std::forward<Args>(args)...);
	}
	/** Call the termination routine of the stored reference.

	\returns 1 if the stored value's termination routine
	succeeded, 0 otherwise.
	*/
	int term()
	{
		if (_init == 0) return 0;
		int t = _value.term();
		if (t) [[likely]]
		{
			_init = 0;
			return 1;
		}
		else [[unlikely]]
		{
			return 0;
		}
	}
	/// Get the value reference, stored inside the raii object.
	const _Ty& get() const { return _value; }
	/// Get the value reference, stored inside the raii object.
	_Ty& get() { return _value; }
	/// A helper operator to access the members of stored value.
	_Ty* operator->()
	{
		return &_value;
	}
	/// Check if the stored value reference is initialized.
	int is_init() const
	{
		return _init;
	}
};

}
}