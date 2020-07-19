#pragma once

using size_t = unsigned long int;
using ssize_t = signed long int;

#ifdef __cplusplus
#define declext extern "C"
#else
#define declext
#endif

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

/// @ret: count of bytes read
declext void read(int __fd, void const *__buf, size_t __len);
/// @ret: count of chars written
declext ssize_t write(int __fd, void const *__buf, size_t __len);

/// @ret: file descriptor
declext int open(char const* __path, int __flags, int __mode);
/// @ret: zero on success, -1 on failure
declext void close(int __fd);

// declext void exit(int retcode);
