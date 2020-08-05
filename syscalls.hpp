#pragma once

using size_t = unsigned long int;
using ssize_t = signed long int;

extern "C" {

/// @ret: count of bytes read
void read(int __fd, void const *__buf, size_t __len);
/// @ret: count of chars written
ssize_t write(int __fd, void const *__buf, size_t __len);

/// @ret: file descriptor
int open(char const* __path, int __flags, int __mode);
/// @ret: zero on success, -1 on failure
void close(int __fd);

// declext void exit(int retcode);
}
