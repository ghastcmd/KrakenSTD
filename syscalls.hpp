#pragma once

typedef unsigned long int size_t;

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
declext void read(int fd, const char *buffer, size_t input_lenght);
/// @ret: count of chars written
declext int write(int fd, const char *buffer, size_t buffer_size);

/// @ret: file descriptor
declext int open(const char* fname, int flags, int mode);
/// @ret: zero on success, -1 on failure
declext void close(int fd);

declext void exit(int retcode);
