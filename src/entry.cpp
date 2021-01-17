#include "syscalls.hpp"
#include "inttypes.hpp"
#include "stlcpp.hpp"

static const char *endl = "\n";

#ifdef __linux__

size_t strlen(const char *str)
{
    const char *ptr = str;
    while (*ptr)
    {
        ptr++;
    }
    return ptr - str;
}

#endif

void print(const char *fmt)
{
    const char *ptr = fmt;
    while (*ptr)
    {
        ptr++;
    }
    size_t len = ptr - fmt;

    write(0, fmt, len);
}

template <typename _ty> requires integral<_ty>
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
    for (;ps_buffer < p_buffer; ps_buffer++, p_buffer--)
    {
        iter_swap(ps_buffer, p_buffer);
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

#ifdef _WIN32

void * CreateFile(
    const char * nm, int desired_access, int share_mode, void * security_attrs,
    int creation_disposition, int flags_n_attr, void * template_file
);

long int write(int fd, void const *buff, unsigned long int len)
{
    (void)fd;
    (void)len;
    (void)buff;

    fd = -10 - fd;

    // void* handle = CreateFile("CONOUT$", 3, 3, nullptr, 3, 0, nullptr);

    void *handle = (void*)-1;

    unsigned int iosb[2];
    NtWriteFile(handle, 0, 0, 0, iosb, (void*)buff, len, 0, 0);
    return iosb[1];
}

extern "C" void exit(int exit_code)
{
    NtTerminateProcess((void*)-1, exit_code);
}

#endif

extern "C" int _entry()
{
    char str1[] = "aewqeqw";
    write(1, str1, sizeof(str1));
    println();
    char str[] = "eqwewq3221321321";

    #ifdef __linux__

    println("simple text i'm writing right now");
    // void * handle;
    // char str[] = "text";
    // unsigned long iost[2];
    // NtWriteFile(handle, 0, 0, 0, &iost, str, sizeof(str), 0, 0);

    #endif

    println(str);

    println(3.14155454);

    return 0;
}