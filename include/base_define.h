#ifndef ECHO_FMT_INCLUDE_BASE_DEFINE_H_
#define ECHO_FMT_INCLUDE_BASE_DEFINE_H_

#include <type_traits>
#include <string>

// Clang
#if defined(__clang__)
#define ECHO_CLANG_VERSION (__clang_major__ * 100 + __clang_minor__)
#else
#define ECHO_CLANG_VERSION 0
#endif

// GCC
#if defined(__GUNC__) && !defined(__clang__)
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

namespace detail {

// 数据类型枚举
enum class Type {
  kNone,
  kInt,
  kUInt,
  kLongLong,
  kULongLong,
  kInt128,
  kUInt128,
  kBool,
  kChar,
  kLastInteger = kChar,
  kFloat,
  kDouble,
  kLongDouble.
  kLastNumeric = kLongDouble,
  kCString,
  kString,
  kPointer,
  kCustom
};

template<typename T, typename C>
struct type_constant : std::integral_constant<Type, Type::kCustom> {};

#define ECHO_TYPE_CONSTANT(type, constant) \
template<typename C>                       \
struct type_constant<type, C> : std::integral_constant<Type, Type::constant>{}

ECHO_TYPE_CONSTANT(int, kInt);
ECHO_TYPE_CONSTANT(unsigned, kUInt);
ECHO_TYPE_CONSTANT(long long, kLongLong);
ECHO_TYPE_CONSTANT(unsigned long long, kULongLong);

}

namespace echofmt {

template<bool X, typename T = void>
using enable_if_t = typename std::enable_if<X, T>::type;

}

#define ECHO_ENABLE_IF(...) echofmt::enable_if_t<(__VA_ARGS__), int> = 0

#endif //ECHO_FMT_INCLUDE_BASE_DEFINE_H_
