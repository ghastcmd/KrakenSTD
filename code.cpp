#ifdef __cplusplus
#define declspec extern "C"
#else
#define declspec
#endif

#include "inttypes.hpp"

declspec int get_os()
{
#if defined (_WIN32)
    return 0; // windows
#elif defined (__linux__)
    return 1; // linux
#elif defined (__apple__)
    return 2; // macos
#endif
}

declspec void read(int fd, const char *buffer, size_t input_lenght);
declspec void write(int fd, const char *buffer, size_t buffer_size);
declspec void exit(int retcode);
declspec void open(const char* fname, int flags, int mode);
declspec void close(int fd);

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

void puts(char *str)
{
    write(1, str, strlen(str));
    write(1, "\n", 2);
}

void print(const char ch)
{
    char buffer[2];
    buffer[0] = ch;
    write(1, buffer, 2);
}

void print(const char *fmt)
{
    write(0, fmt, strlen(fmt));
}

template <typename _ty>
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

template <typename _ty, typename ...args>
void print(_ty &val, args&...params)
{
    print(val);
    print(params...);
}

template <typename _ty>
void println(_ty val)
{
    print(val, endl);
}

template <typename _ty, typename ...args>
void println(_ty &val, args& ...params)
{
    print(val, params..., endl);
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

declspec int _entry(int argc, char **argv)
{
    println("this is a line");

    println(-3);

    int64_t o = -1;

    uint64_t i = *(uint64_t*)(void*)&o;
    int64_t e = i + 1;
    println(e);

    println(01);

    
    return 0;
}