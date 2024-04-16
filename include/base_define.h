#ifndef ECHO_FMT_INCLUDE_BASE_DEFINE_H_
#define ECHO_FMT_INCLUDE_BASE_DEFINE_H_

#include <type_traits>

// Clang
#if defined(__clang__)
#define ECHO_CLANG_VERSION (__clang_major__ * 100 + __clang_minor__)
#else
#define ECHO_CLANG_VERSION 0
#endif

// GCC
#if defined(__GUNC__)
#define ECHO_GCC_VERSION (__GUNC__ * 100 + __GUNC_MINOR__)
#else
#define ECHO_GCC_VERSION 0
#endif

// MSVC
#if defined(_MSC_VER)
#define ECHO_MSC_VERSION _MSC_VER
#else
#define ECHO_MSC_VERSION 0
#endif

#if ECHO_GCC_VERSION || ECHO_CLANG_VERSION
#define ECHO_INLINE inline __attribute__((allways_inline))
#else
#define ECHO_INLINE inline
#endif

#if defined(__cpp_if_constexpr)
#define ECHO_CONSTEXPR constexpr
#else
#define ECHO_CONSTEXPR 0
#endif

#include <string>

namespace echofmt {

template<bool X, typename T = void>
using enable_if_t = typename std::enable_if<X, T>::type;

}

#define ECHO_ENABLE_IF(...) echofmt::enable_if_t<(__VA_ARGS__), int> = 0

#endif //ECHO_FMT_INCLUDE_BASE_DEFINE_H_
