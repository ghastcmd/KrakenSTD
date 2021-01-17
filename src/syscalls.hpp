#pragma once

extern "C" {

/// @ret: count of bytes read
void read(int __fd, void const *__buf, unsigned long int __len);
/// @ret: count of chars written
long int write(int __fd, void const *__buf, unsigned long int __len);

/// @ret: file descriptor
int open(char const* __path, int __flags, int __mode);
/// @ret: zero on success, -1 on failure
void close(int __fd);

unsigned long NtWriteFile(
    void *handle, void *event, void *acp_routine, void *apc_context, 
    unsigned int status_block[2], void *buffer, unsigned long len, 
    void *byte_offset, unsigned int *key
);

unsigned long NtCreateFile(
    void **handle, int desired_access, void *object_attributes, 
    unsigned int statuc_block[2], void *allocation_size, unsigned int attrs, 
    unsigned int share_access, unsigned int create_disposition, 
    unsigned int create_options, void *buffer, unsigned int len
);

bool NtTerminateProcess(void * handle, unsigned int exit_code);

// void exit(int retcode);
}
