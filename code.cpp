#ifdef __cplusplus
#define declext extern "C"
#else
#define declext
#endif

#include "inttypes.hpp"

declext int get_os()
{
#if defined (_WIN32)
    return 0; // windows
#elif defined (__linux__)
    return 1; // linux
#elif defined (__apple__)
    return 2; // macos
#endif
}

declext void read(int fd, const char *buffer, size_t input_lenght);
declext void write(int fd, const char *buffer, size_t buffer_size);
declext void exit(int retcode);
declext void open(const char* fname, int flags, int mode);
declext void close(int fd);

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

void print(const char ch)
{
    char buf[] = "\0\0";
    *buf = ch;
    write(1, buf, 2);
}

void print(const char *fmt)
{
    write(0, fmt, strlen(fmt));
}

template <typename _ty>
auto print(const _ty val) -> enable_if_t<is_integer<_ty>()>
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

    if constexpr(!is_unsigned<_ty>())
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

template <typename _ty, typename ..._args>
void print(_ty val, _args...args)
{
    return (print(val), print(' '), print(args...));
}

template <typename _ty>
void println(_ty val)
{
    print(val, endl);
}

template <typename _ty, typename ..._args>
void println(_ty val, _args...args)
{
    return (print(val), println(args...));
}

struct al
{
    int val;
    al(int v) : val(v) {}
};

void print(al &val)
{
    print((uint64_t)val.val);
}

declext int _entry(int argc, char **argv)
{
    println("this ", "is ", "ad-absurdum ", 10 * 2000 + 40);

    print(endl);

    print(300, endl);


    return 0;
}