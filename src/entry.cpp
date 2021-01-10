#include "syscalls.hpp"
#include "inttypes.hpp"

static const char *endl = "\n";

template <typename _ty>
void swap(_ty &f, _ty &l) { _ty ax = f; f = l; l = ax; }

template <typename _ty>
void iter_swap(_ty *f, _ty *l) { _ty ax = *f; *f = *l; *l = ax; }

size_t strlen(const char *str)
{
    const char *ptr = str;
    while (*ptr)
    {
        ptr++;
    }
    return ptr - str;
}

void print(const char *fmt)
{
    write(0, fmt, strlen(fmt));
}

template <typename _ty> requires integer<_ty>
void print(const _ty val)
{
    if (val == 0)
    {
        print("0");
        return;
    }

    char buffer[sizes<_ty>::len];
    char *p_buffer = buffer;
    char *ps_buffer = buffer;
    _ty tval = val;

    if constexpr(!is_unsigned_v<_ty>)
    {
        if (val < 0)
        {
            *p_buffer++ = '-';
            tval = -val;
            ++ps_buffer;
        }
    }

    while (tval)
    {
        *p_buffer++ = tval % 10 + '0';
        tval /= 10;
    }

    *p_buffer-- = 0;
    while (ps_buffer < p_buffer)
    {
        iter_swap(ps_buffer++, p_buffer--);
    }
    print((const char*)buffer);
}

template <typename _ty> requires floating<_ty>
void print(const _ty val) 
{
    extern size_t to_float(char *, float, int = 6);
    char buffer[10];
    to_float(buffer, val);
    print(buffer);
}


inline void println()
{
    print(endl);
}

template <typename _ty>
inline constexpr void println(_ty val)
{
    print(val);
    print(endl);
}

template <typename _ty, typename ..._args>
inline constexpr void println(_ty val, _args...args)
{
    return (print(val), println(args...));
}

extern "C" int _entry()
{
    char str1[] = "aewqeqw";
    write(1, str1, sizeof(str1));
    println();
    char str[] = "eqwewq3221321321";

    println(str);

    println(3.14155454);

    return 0;
}