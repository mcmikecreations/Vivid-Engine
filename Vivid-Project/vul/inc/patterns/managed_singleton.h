#pragma once

#include <memory>
#include <type_traits>

#include "core.h"

namespace vul {
namespace patterns {
/** \brief Allows to manage lifetime of a singleton value.

Managed singleton is similar to the singleton pattern, but
allows users to strictly manage the lifetime of the underlying
value.

\tparam _Ty The type of the value.
\tparam _Alloc Allocator type used to create and destroy the
	value. By default _Alloc is an std::allocator, meaning that the
	new and delete operators will be used.
*/
template<class _Ty, template <class> class _Alloc = std::allocator >
class managed_singleton
{
public:
	/// The type of the value, stored in the managed_singleton.
	using value_type = _Ty;
	/** \brief The type of the allocator, stored in the
	managed_singleton and used to create and destroy the value.
	*/
	using allocator_type = _Alloc<_Ty>;
private:
	using _Alty_traits = std::allocator_traits<allocator_type>;

	static _Ty* _value;
	allocator_type _allocator;
	bool _init;
public:
	managed_singleton(managed_singleton const&) = delete;
	void operator=(managed_singleton const&) = delete;
	///Construct the singleton with a default allocator.
	managed_singleton()
		: _allocator(), _init(false)
	{  }
	/** Construct the singleton, copying the allocator.

	\param[in] al The allocator to copy into the singleton
	*/
	managed_singleton(const allocator_type& al)
		: _allocator(al), _init(false)
	{ }
	/** \brief Initialize the singleton with the given
		arguments.

	This function is used to construct the internal singleton
	value with the given arguments. First, free space is created
	to store the value. Then the object is constructed in-place.

	\tparam Args The argument types, passed to the value
	constructor.
	\param[in] args The arguments, passed to the value
	constructor.
	\returns 1 if the singleton was initialized, 0 otherwise.
	*/
	template<class ...Args>
	int init(Args... args)
	{
		if (_init) return 0;
		_value = _Alty_traits::allocate(_allocator, 1);
		if (_value == nullptr) return 0;
		_Alty_traits::construct(_allocator, _value, std::forward<Args>(args)...);
		_init = true;
		return 1;
	}
	/** Terminate the value, stored inside the singleton.

	\returns 1 if the value was terminated, 0 otherwise.
	*/
	int term()
	{
		if (!_init) return 0;
		_Alty_traits::destroy(_allocator, _value);
		_Alty_traits::deallocate(_allocator, _value, 1);
		_value = nullptr;
		_init = false;
		return 1;
	}
	/// Get a value reference from the singleton.
	static _Ty& get()
	{
		return *_value;
	}
	/// Get a value pointer from the singleton.
	static _Ty* ptr()
	{
		return _value;
	}
};
}
}

template <class _Ty, template <class> class _Alloc>
_Ty* vul::patterns::managed_singleton<_Ty, _Alloc>::_value = nullptr;
