#pragma once

using uint64_t = unsigned long long int;
using uint32_t = unsigned int;
using uint16_t = unsigned short;
using uint8_t  = unsigned char;

using int64_t = signed long long int;
using int32_t = signed int;
using int16_t = signed short;
using int8_t  = signed char;

#ifdef __linux__
using size_t  = unsigned long int;
using ssize_t = signed long int;
#else
using size_t  = unsigned long long int;
using ssize_t = signed long long int;
#endif

using byte    = unsigned char;

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

#ifdef __linux__

template <>
struct sizes <size_t> {
    using type = size_t;
    static constexpr type max = 0xffffffffffffffff;
    static constexpr type min = 0x0000000000000000;
    static constexpr byte len = 20;
};

#endif

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


template <>
struct sizes <float> {
    using type = float;
    static constexpr type len = 15;
};

template <>
struct sizes <double> {
    using type = double;
    static constexpr type len = 24;
};


template <typename _ty>
constexpr byte hex_len = sizeof(sizes<_ty>::max) * 2 + 2;


template <typename _ty, _ty val>
struct lit_val
{ static constexpr _ty value = val; };

using true_type  = lit_val<bool, true>;
using false_type = lit_val<bool, false>;


template <typename _ty>
struct is_integer : false_type {};

template <>
struct is_integer <int8_t>   : true_type {};

template <>
struct is_integer <int16_t>  : true_type {};

template <>
struct is_integer <int32_t>  : true_type {};

template <>
struct is_integer <int64_t>  : true_type {};

template <>
struct is_integer <uint8_t>  : true_type {};

template <>
struct is_integer <uint16_t> : true_type {};

template <>
struct is_integer <uint32_t> : true_type {};

template <>
struct is_integer <uint64_t> : true_type {};

#ifdef __linux__

template <>
struct is_integer <size_t>   : true_type {};

#endif

template <typename _ty>
constexpr bool is_integer_v = is_integer<_ty>::value;

template <typename _ty>
constexpr bool integral = is_integer_v<_ty>;


template <typename _ty>
struct is_floating : false_type {};

template <>
struct is_floating <float> : true_type {};

template <>
struct is_floating <double> : true_type {};

template <typename _ty>
constexpr bool is_floating_v = is_floating<_ty>::value;

// template <typename _ty>
// constexpr bool floating = is_floating_v<_ty>;

template <typename _ty>
concept floating = is_floating_v<_ty>;


template <typename _ty>
struct is_unsigned : false_type {};

template <>
struct is_unsigned <uint8_t>  : true_type {};

template <>
struct is_unsigned <uint16_t> : true_type {};

template <>
struct is_unsigned <uint32_t> : true_type {};

template <>
struct is_unsigned <uint64_t> : true_type {};


template <typename _ty>
constexpr bool is_unsigned_v = is_unsigned<_ty>::value;


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



template <typename _ty1, typename _ty2>
struct is_same : false_type {};

template <typename _ty>
struct is_same<_ty, _ty> : true_type {};

template <typename _ty1, typename _ty2>
constexpr bool is_same_v = is_same<_ty1, _ty2>::value;