#pragma once
#ifndef CLT_DEFINES_HPP_
#define CLT_DEFINES_HPP_

#if __cplusplus < 202002L
#error "Library is intended to be compiled with C++20 or later."
#endif

#if __cplusplus >= 201103L
#define CLT_CPP11 11
#endif

#if __cplusplus >= 201402L
#define CLT_CPP14 14
#endif

#if __cplusplus >= 201703L
#define CLT_CPP17 17
#endif

#if __cplusplus >= 202002L
#define CLT_CPP20 20
#endif

#if __cplusplus >= 202100L
#define CLT_CPP23 23
#endif

#ifdef CLT_CPP11
#define CLT_CONSTEXPR constexpr
#define CLT_EXPLICIT explicit
#define CLT_NOEXCEPT noexcept
#define CLT_INLINE inline
#endif

#ifdef CLT_CPP14
#endif

#ifdef CLT_CPP17
#define CLT_NODISCARD [[nodiscard]]
#define CLT_MAYBE_UNUSED [[maybe_unused]]
#define CLT_NOEXCEPT_WITH(s) noexcept(s)
#endif

#ifdef CLT_CPP20

#define CLT_CONSTEVAL consteval
#define CLT_CONCEPT concept
#define CLT_REQUIRES requires

#define CLT_EXPLICIT_WITH(s) explicit(s)

#define CLT_NODISCARD_BECAUSE(s) [[nodiscard(s)]]

#if defined(__cpp_lib_format) && __cpp_lib_format >= 201907L
#define CLT_CPP_FORMAT20
#endif

#endif

#endif