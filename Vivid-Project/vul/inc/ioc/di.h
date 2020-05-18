#pragma once

#include <map>
#include <tuple>
#include <set>
#include <functional>
#include <type_traits>
#include <memory_resource>
#include <algorithm>

#include "errors.h"
#include "ioc/di_scope.h"
#include "ioc/di_scope_transient.h"
#include "ioc/di_scope_singleton.h"

namespace vul {
namespace ioc {
/// An IoC Container
class di
{
private:
	using function_parameter_reference = di&;
	using function_type = std::function< di_basic_scope* (function_parameter_reference) >;
	template <class _Ty>
	using allocator_type = std::pmr::polymorphic_allocator<_Ty>;
	using cache_destructor_type = std::function< int(bool*, void*, di_basic_scope*) >;
	using cache_value_type = std::tuple<std::size_t, bool*, void*, di_basic_scope*, cache_destructor_type>;
	struct less {
		constexpr bool operator()(const cache_value_type& _Left, const cache_value_type& _Right) const {
			return std::get<di_basic_scope*>(_Left) < std::get<di_basic_scope*>(_Right);
		}
	};
	using cache_container_type = std::set<cache_value_type, less, allocator_type<cache_value_type>>;

	std::pmr::memory_resource* _memory;
	std::map<
		std::size_t,
		function_type,
		std::less<std::size_t>,
		allocator_type<
		std::pair<const std::size_t, function_type>
		>
	> _class_map;
	allocator_type<std::byte> _alloc;
	cache_container_type _scope_cache;
	di_scope_singleton<di> _this_scope;
	bool _this_scope_is_scope;

	template <class _T>
	inline std::size_t key()
	{
		//cv-qualifiers are ignored for typeid, but this is done
		//to explicitly show what is happening
		using _U0 = std::remove_cv<_T>::type;
		using _U1 = std::remove_reference<_U0>::type;
		using _U2 = std::remove_pointer<_U1>::type;
		using _U = _U2;
		return typeid(_U).hash_code();
	}

	template <class _T>
	int add(const function_type& f)
	{
		auto p = _class_map.find(key<_T>());
		if (p == _class_map.end())
		{
			auto res = _class_map.insert(std::make_pair(key<_T>(), f));
			return res.second ? (int)vul::error::success : (int)vul::error::failure;
		}
		else
		{
			p->second = f;
			return (int)vul::error::success;
		}
	}

	int erase_scopes(bool all)
	{
		int failures = 0;
		for (auto p = _scope_cache.begin(); p != _scope_cache.end();)
		{
			bool shouldDelete = !*(std::get<bool*>(*p)) || all;
			if (shouldDelete)
			{
				//TODO - we can gather failed attempts by collecting iterators to cache that wasn't erased
				int res = std::get<cache_destructor_type>(*p)(
					std::get<bool*>(*p),
					std::get<void*>(*p),
					std::get<di_basic_scope*>(*p)
					);
				if (res == (int)vul::error::success)
				{
					p = _scope_cache.erase(p);
				}
				else
				{
					++failures;
					++p;
				}
			}
			else
			{
				++p;
			}
		}
		return failures == 0 ? (int)vul::error::success : (int)vul::error::failure;
	}

	int erase_scope(cache_container_type::const_iterator p)
	{
		if (p == _scope_cache.end()) 
			return (int)vul::error::value_empty;

		di_basic_scope* m_scope = std::get<di_basic_scope*>(*p);
		bool* m_bool = std::get<bool*>(*p);
		m_scope->set_scope(false);
		//We failed to change the scope state. Used for singleton.
		if (m_scope->is_scope()) 
			return (int)vul::error::failure;

		int res = std::get<cache_destructor_type>(*p)(
			m_bool,
			std::get<void*>(*p),
			m_scope
			);
		if (res == (int)vul::error::success)
		{
			_scope_cache.erase(p);
			return res;
		}
		return (int)vul::error::failure;
	}

	int insert_cache(const cache_value_type& value)
	{
		auto p = _scope_cache.insert(
			value
		);
		return std::get<bool>(p) ? (int)vul::error::success : (int)vul::error::failure;
	}

	auto find_cache(di_basic_scope* scope)
	{
		return std::find_if(_scope_cache.begin(), _scope_cache.end(), [scope](const cache_value_type& val) -> bool
			{
				return std::get<di_basic_scope*>(val) == scope;
			});
	}

	auto find_cache_value(void* value)
	{
		return std::find_if(_scope_cache.begin(), _scope_cache.end(), [value](const cache_value_type& val) -> bool
			{
				return std::get<void*>(val) == value;
			});
	}

	auto find_cache_key(std::size_t m_key)
	{
		return std::find_if(_scope_cache.begin(), _scope_cache.end(), [m_key](const cache_value_type& val) -> bool
			{
				return std::get<std::size_t>(val) == m_key;
			});
	}

	template <class _T>
	auto find_cache_key()
	{
		std::size_t m_key = key<_T>();
		return std::find_if(_scope_cache.begin(), _scope_cache.end(), [m_key](const cache_value_type& val) -> bool
			{
				return std::get<std::size_t>(val) == m_key;
			});
	}
public:
	/** Construct an IoC Container using a prepared
	memory_resource.

	\param[in] resource Memory resource, that will be used for
	all internal allocations.
	*/
	di(std::pmr::memory_resource* resource = std::pmr::get_default_resource())
		: _memory(resource),
		_class_map(resource),
		_alloc(resource),
		_scope_cache(resource),
		_this_scope(&_this_scope_is_scope, this, this)
	{}
	/** Initialize the IoC Container.
	
	\returns success if succeeded, failure otherwise.
	*/
	int init() { return (int)vul::error::success; }
	/** Call termination routine of the IoC Container, clear
	scope and mapping cache.
	
	\returns success if succeeded, error otherwise.
	*/
	int term() { return erase_scopes(true); }

	/** Manually free the scope from the IoC Container cache.

	\param[in] scope The scope to free from cache.
	\param[in] immediate Whether to free the value immediately
	or scedule it for the next cache clear routine.
	\exception error::value_empty A nullptr scope was given.
	\exception error::context_mismatch DI context of scope
	doesn't match.
	\exception error::failure Din't free the scope.
	\returns success if succeeded, error otherwise.
	*/
	int free(di_basic_scope* scope, bool immediate = true)
	{
		if (scope == nullptr) return (int)vul::error::value_empty;
		if (scope->di() != (void*)this) return (int)vul::error::context_mismatch;
		auto p = find_cache(scope);
		if (p != _scope_cache.end())
		{
			if (immediate)
			{
				return erase_scope(p);
			}
			else
			{
				return std::get<di_basic_scope*>(*p)->set_scope(false);
			}
		}
		return (int)vul::error::failure;
	}

	/** Manually free the value from the IoC Container cache.

	\param[in] value The value to free from cache.
	\param[in] immediate Whether to free the value immediately
	or scedule it for the next cache clear routine.
	\exception error::value_empty A nullptr scope was given.
	\exception error::context_mismatch DI context of scope
	doesn't match.
	\exception error::failure Din't free the scope.
	\returns success if succeeded, error otherwise.
	*/
	int free(void* value, bool immediate = true)
	{
		if (value == nullptr) return (int)vul::error::value_empty;
		auto p = find_cache_value(value);
		if (p != _scope_cache.end())
		{
			if (immediate)
			{
				return erase_scope(p);
			}
			else
			{
				return std::get<di_basic_scope*>(*p)->set_scope(false);
			}
		}
		return (int)vul::error::failure;
	}

	/** Clears scope cache of the IoC Container, leaves mapping
	cache intact.

	\returns success if succeeded, error otherwise.
	*/
	int clear()
	{
		return erase_scopes(false);
	}
	/** Get a value, wrapped in a scope, from the IoC Container.

	\tparam _T The type of value (interface) to get, no pointer
	or reference needed.
	\returns Scope from the IoC Container if succeeded, nullptr
	otherwise.
	*/
	template <class _T>
	di_scope<_T>* get()
	{
		std::size_t _key = key<_T>();
		if (_key == key<di>()) return dynamic_cast<di_scope<_T>*>(&_this_scope);
		auto p = _class_map.find(_key);
		if (p == _class_map.end()) return nullptr;
		return static_cast<di_scope<_T>*>(p->second(*this));
	}
	/** Construct a class using the values, provided by the IoC
	Container. The value is not tracked by the memory manager.

	\tparam _T The type of object to construct.
	\tparam Args The arguments, that will be passed to the
	constructor of _T, no pointer or reference needed. All of
	the arguments inside the constructor have to be pointers.
	\returns The constructed object if succeeded, nullptr
	otherwise.
	*/
	template <class _T, class ...Args>
	_T* construct()
	{
		std::tuple<di_scope<Args>*...> args(get<Args>()...);

		std::byte* p_value_bytes = get_allocator().allocate(sizeof(_T));
		if (p_value_bytes == nullptr) return nullptr;
		_T* p_value = new (p_value_bytes) _T(static_cast<Args*>(std::get<di_scope<Args>*>(args)->ptr())...);
		return p_value;
	}
	/** \brief Destroy an object, constructed by the IoC
	Container.

	Does not destroy or free the scopes, that were passed as
	constructor parameters. It is upon the user to check if
	the object was constructed by the IoC Container instance.

	\tparam _T The type of object to destroy.
	\param[in] value The object to destroy.
	*/
	template <class _T>
	void destruct(_T* value)
	{
		value->~_T();
		get_allocator().deallocate(reinterpret_cast<std::byte*>(value), sizeof(_T));
	}
	/// Get the internal allocator, used by the IoC Container.
	allocator_type<std::byte>& get_allocator() { return _alloc; }
	/** \brief Add an interface and implementation to the
	transient mapping cache.

	Add a transient factory method to create objects of type
	_ImV, when requested using the interface of type _InT. On
	every subsequent call of `get<_InT>()` a new instance of
	_ImV will be constructed.

	\tparam _InT The interface to use for mapping. Use this type
	to get instances in the future.
	\tparam _ImV The implementation to use for mapping. Objects
	of this type are constructed, when calling `get<_InT>()`.
	\tparam Args The arguments of _ImV to use during
	construction. All arguments are constructed by the IoC
	Container, so it is not possible to pass additional
	arguments.
	\returns success if added, failure otherwise.
	*/
	template <class _InT, class _ImV, class ...Args>
	int add_transient()
	{
		//Better rewritten to support concepts
		static_assert(std::is_convertible<_ImV*, _InT*>::value, "_ImV should be an implementation of _InT");

		auto func = [](function_parameter_reference o_di) -> di_basic_scope*
		{
			//Better rewritten with a polymorphic allocator and a memory resource
			//May be wise to store allocators together in a separate place
			std::tuple<di_scope<Args>*...> args(o_di.get<Args>()...);
			//Construct inner value _ImV with args
			std::byte* p_value_bytes = o_di.get_allocator().allocate(sizeof(_ImV));
			if (p_value_bytes == nullptr) return nullptr;
			_ImV* p_value = new (p_value_bytes) _ImV(static_cast<Args*>(std::get<di_scope<Args>*>(args)->ptr())...);

			using scope = di_scope_transient<_InT>;
			//Construct bool
			std::byte* b_value_bytes = o_di.get_allocator().allocate(sizeof(bool));
			if (b_value_bytes == nullptr) [[unlikely]]
			{
				//Destroy previously acquired resources
				p_value->~_ImV();
				o_di.get_allocator().deallocate(p_value_bytes, sizeof(_ImV));
				return nullptr;
			}
			bool* b_scope = reinterpret_cast<bool*>(b_value_bytes);
			*b_scope = scope::initial_scope::value;

			//Construct outer scope<_InT> with p
			std::byte* p_scope_bytes = o_di.get_allocator().allocate(sizeof(scope));
			if (p_scope_bytes == nullptr) [[unlikely]]
			{
				//Destroy previously acquired resources
				o_di.get_allocator().deallocate(b_value_bytes, sizeof(bool));
				p_value->~_ImV();
				o_di.get_allocator().deallocate(p_value_bytes, sizeof(_ImV));
				return nullptr;
			}
			scope* p_scope = new (p_scope_bytes) scope(b_scope, p_value, &o_di);

			o_di.insert_cache(
				std::make_tuple(
					o_di.key<_InT>(),
					b_scope,
					(void*)p_value,
					static_cast<di_basic_scope*>(p_scope),
					[](bool* b, void* v, di_basic_scope* s) -> int
					{
						scope* m_scope = reinterpret_cast<scope*>(s);
						_ImV* m_value = reinterpret_cast<_ImV*>(v);
						di* m_di = reinterpret_cast<di*>(m_scope->di());

						m_scope->~scope();
						m_di->get_allocator().deallocate(reinterpret_cast<std::byte*>(m_scope), sizeof(scope));
						m_di->get_allocator().deallocate(reinterpret_cast<std::byte*>(b), sizeof(bool));
						m_value->~_ImV();
						m_di->get_allocator().deallocate(reinterpret_cast<std::byte*>(m_value), sizeof(_ImV));

						return 1;
					})
			);
			return static_cast<di_basic_scope*>(p_scope);
		};
		//Better rewritten to support both get<_InT> and get<_ImV>
		return add<_InT>(func);
	}
	/** \brief Add an interface and implementation to the
	singleton mapping cache.

	Add a singleton factory method to create objects of type
	_ImV, when requested using the interface of type _InT. On
	every subsequent call of `get<_InT>()` the same instance of
	_ImV will be returned.

	\tparam _InT The interface to use for mapping. Use this type
	to get instances in the future.
	\tparam _ImV The implementation to use for mapping. Objects
	of this type are constructed, when calling `get<_InT>()`.
	\tparam Args The arguments of _ImV to use during
	construction. All arguments are constructed by the IoC
	Container, so it is not possible to pass additional
	arguments.
	\returns success if added, failure otherwise.
	*/
	template <class _InT, class _ImV, class ...Args>
	int add_singleton()
	{
		//Better rewritten to support concepts
		static_assert(std::is_convertible<_ImV*, _InT*>::value, "_ImV should be an implementation of _InT");

		auto func = [](function_parameter_reference o_di) -> di_basic_scope*
		{
			auto it = o_di.find_cache_key<_InT>();
			if (it != o_di._scope_cache.end())
				return std::get<di_basic_scope*>(*it);
			//Better rewritten with a polymorphic allocator and a memory resource
			//May be wise to store allocators together in a separate place
			std::tuple<di_scope<Args>*...> args(o_di.get<Args>()...);
			//Construct inner value _ImV with args
			std::byte* p_value_bytes = o_di.get_allocator().allocate(sizeof(_ImV));
			if (p_value_bytes == nullptr) return nullptr;
			_ImV* p_value = new (p_value_bytes) _ImV(static_cast<Args*>(std::get<di_scope<Args>*>(args)->ptr())...);

			using scope = di_scope_singleton<_InT>;
			//Construct bool
			std::byte* b_value_bytes = o_di.get_allocator().allocate(sizeof(bool));
			if (b_value_bytes == nullptr) [[unlikely]]
			{
				//Destroy previously acquired resources
				p_value->~_ImV();
				o_di.get_allocator().deallocate(p_value_bytes, sizeof(_ImV));
				return nullptr;
			}
			bool* b_scope = reinterpret_cast<bool*>(b_value_bytes);
			*b_scope = scope::initial_scope::value;

			//Construct outer scope<_InT> with p
			std::byte* p_scope_bytes = o_di.get_allocator().allocate(sizeof(scope));
			if (p_scope_bytes == nullptr) [[unlikely]]
			{
				//Destroy previously acquired resources
				o_di.get_allocator().deallocate(b_value_bytes, sizeof(bool));
				p_value->~_ImV();
				o_di.get_allocator().deallocate(p_value_bytes, sizeof(_ImV));
				return nullptr;
			}
			scope* p_scope = new (p_scope_bytes) scope(b_scope, p_value, &o_di);

			o_di.insert_cache(
				std::make_tuple(
					o_di.key<_InT>(),
					b_scope,
					(void*)p_value,
					static_cast<di_basic_scope*>(p_scope),
					[](bool* b, void* v, di_basic_scope* s) -> int
					{
						scope* m_scope = reinterpret_cast<scope*>(s);
						_ImV* m_value = reinterpret_cast<_ImV*>(v);
						di* m_di = reinterpret_cast<di*>(m_scope->di());

						m_scope->~scope();
						m_di->get_allocator().deallocate(reinterpret_cast<std::byte*>(m_scope), sizeof(scope));
						m_di->get_allocator().deallocate(reinterpret_cast<std::byte*>(b), sizeof(bool));
						m_value->~_ImV();
						m_di->get_allocator().deallocate(reinterpret_cast<std::byte*>(m_value), sizeof(_ImV));

						return 1;
					})
			);
			return static_cast<di_basic_scope*>(p_scope);
		};
		//Better rewritten to support both get<_InT> and get<_ImV>
		return add<_InT>(func);
	}

	template <class _InT, class _ImV>
	int add_call() = delete;

	template <class _InT, class _ImV>
	int add_thread() = delete;

	template <class _InT, class _ImV>
	int add_core() = delete;

	template <class _InT, class _ImV>
	int add_scoped() = delete;
};

}
}