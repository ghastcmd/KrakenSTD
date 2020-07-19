#include "syscalls.hpp"
#include "inttypes.hpp"

static const char *endl = "\n";

template <typename _ty>
void swap (_ty &f, _ty &l) { _ty ax = f; f = l; l = ax; }

template <typename _ty>
void iter_swap(_ty *f, _ty *l) { _ty ax = *f; *f = *l; *l = ax; }

size_t strlen(const char *str)
{
    const char *ptr = str;
    while (*ptr++);
    return ptr - str;
}

void print(const char *fmt)
{
    write(0, fmt, strlen(fmt));
}

template <typename _ty>
auto print(const _ty val) -> enable_if_t<is_integer<_ty>::value>
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

    if constexpr(!is_unsigned<_ty>::value)
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



struct dummy_inline
{ template <typename ..._args> dummy_inline(_args...) {} };

template <typename ..._args>
inline void dummy_inline_func(_args...args) {}



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

declext int _entry()
{

    println(sizeof(dummy_inline));
    
    return 0;
}