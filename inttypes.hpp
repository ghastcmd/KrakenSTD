#pragma once

using uint64_t = unsigned long long;
using uint32_t = unsigned int;
using uint16_t = unsigned short;
using uint8_t  = unsigned char;

using int64_t = signed long long;
using int32_t = signed int;
using int16_t = signed short;
using int8_t  = signed char;

using size_t = uint64_t;
using byte = uint8_t;

template <typename _ty>
struct sizes {};

template <>
struct sizes <uint8_t> {
    using type = uint8_t;
    static constexpr type max = 0xff;
    static constexpr type min = 0x00;
    static constexpr byte len = 3;
};

template <>
struct sizes <uint16_t> {
    using type = uint16_t;
    static constexpr type max = 0xffff;
    static constexpr type min = 0x0000;
    static constexpr byte len = 5;
};

template <>
struct sizes <uint32_t> {
    using type = uint32_t;
    static constexpr type max = 0xffffffff;
    static constexpr type min = 0x00000000;
    static constexpr byte len = 10;
};

template <>
struct sizes <uint64_t> {
    using type = uint64_t;
    static constexpr type max = 0xffffffffffffffff;
    static constexpr type min = 0x0000000000000000;
    static constexpr byte len = 20;
};




template <>
struct sizes <int8_t> {
    using type = int8_t;
    static constexpr type max = 0x7f;
    static constexpr type min = -0x7f;
    static constexpr byte len = 4;
};

template <>
struct sizes <int16_t> {
    using type = int16_t;
    static constexpr type max = 0x7fff;
    static constexpr type mix = -0x7fff;
    static constexpr byte len = 6;
};

template <>
struct sizes <int32_t> {
    using type = int32_t;
    static constexpr type max = 0x7fffffff;
    static constexpr type min = -0x7fffffff;
    static constexpr byte len = 11;
};

template <>
struct sizes <int64_t> {
    using type = int64_t;
    static constexpr type max = 0x7fffffffffffffff;
    static constexpr type min = -0x7fffffffffffffff;
    static constexpr byte len = 20;
};



template <typename _ty>
constexpr bool is_integer()
{ return false; }

template <>
constexpr bool is_integer <int8_t>()
{ return true; }

template <>
constexpr bool is_integer <int16_t>()
{ return true; }

template <>
constexpr bool is_integer <int32_t>()
{ return true; }

template <>
constexpr bool is_integer <int64_t>()
{ return true; }

template <>
constexpr bool is_integer <uint8_t>()
{ return true; }

template <>
constexpr bool is_integer <uint16_t>()
{ return true; }

template <>
constexpr bool is_integer <uint32_t>()
{ return true; }

template <>
constexpr bool is_integer <uint64_t>()
{ return true; }




template <typename _ty>
constexpr bool is_unsigned()
{ return false; }

template <>
constexpr bool is_unsigned <uint8_t>()
{ return true; }

template <>
constexpr bool is_unsigned <uint16_t>()
{ return true; }

template <>
constexpr bool is_unsigned <uint32_t>()
{ return true; }

template <>
constexpr bool is_unsigned <uint64_t>()
{ return true; }


template <bool _test, typename _ty = void>
struct enable_if {};

template <typename _ty>
struct enable_if<true, _ty> {
    using type = _ty;
};

template <typename _ty>
struct enable_if<false, _ty> {};

template <bool _test, typename _ty = void>
using enable_if_t = typename enable_if<_test, _ty>::type;