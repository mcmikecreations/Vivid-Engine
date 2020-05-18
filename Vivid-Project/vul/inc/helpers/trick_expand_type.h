#pragma once

#include <tuple>

namespace vul
{
namespace helpers
{
/// Get first type from template parameter pack.
template <class _F, class ..._Other>
struct first_type
{
	using type = _F;
};
/// Get Nth type from template parameter pack.
template<class ..._Args>
struct nth_type
{
	// Use tuple directly instead of stealing its implementation.
	template <std::size_t _N>
	using type = decltype(std::get<_N>(std::tuple<_Args...>{}));
};
}
}