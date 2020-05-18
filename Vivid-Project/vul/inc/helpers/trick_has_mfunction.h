#pragma once

///Use SFINAE to check if a function with `function_name` exists.
#define DECL_HAS_MEMBER_FUNCTION(function_name) \
namespace vul { namespace helpers { \
template <typename T> \
class has_ ## function_name \
{ \
    typedef char one; \
    struct two { char x[2]; }; \
\
    template <typename C> static one test(decltype(&C::function_name)); \
    template <typename C> static two test(...); \
\
public: \
    enum { value = sizeof(test<T>(0)) == sizeof(char) }; \
};}}