#include <windows.h>
#include <stdio.h>
#include <winternl.h>
#include <ntdef.h>
#include <wchar.h>

extern "C" {

    // bool WriteFileP(
    //     void *handle, const void *buffer, int len, DWORD *written, void *reserved
    // );

    // bool WriteFileP(
    //     HANDLE handle, LPCVOID buffer, DWORD len, LPDWORD written,
    //     LPOVERLAPPED reserved
    // );

    NTSTATUS NtWriteFileP(
        HANDLE handle, HANDLE event, PIO_APC_ROUTINE apc_routine, PVOID apc_context,
        PIO_STATUS_BLOCK status_block, PVOID buffer, ULONG lenght,
        PLARGE_INTEGER byte_offset, PULONG key
    );

    NTSTATUS NtCreateFileP(
        PHANDLE handle, ACCESS_MASK desired_access, POBJECT_ATTRIBUTES obj_attrs,
        PIO_STATUS_BLOCK status_block, PLARGE_INTEGER alloc_size,
        ULONG file_attrs, ULONG shared_access, ULONG create_disposition,
        ULONG create_options, PVOID ea_buffer, ULONG ea_buffer_len
    );

    // HANDLE CreateFileP(
    //     LPCSTR file_name, DWORD desired_access, DWORD share_mode, 
    //     LPSECURITY_ATTRIBUTES security_attrs,
    //     DWORD creation_disposition, DWORD flags_n_attr, 
    //     HANDLE template_file
    // );

    bool PerformanceP(LARGE_INTEGER *lp);
    NTSTATUS NtQueryPerformanceCounter(
        PLARGE_INTEGER pcounter, PLARGE_INTEGER pfreq
    );
    bool normal_func(void*);

}

void print_error()
{
    char * buffer = nullptr;

    FormatMessageA(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | 
        FORMAT_MESSAGE_FROM_SYSTEM | 
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPSTR)&buffer, 0, NULL
    );

    puts(buffer);
}

void * CreateFilePP(const char * file_name)
{
    const unsigned short lenght = strlen(file_name);
    HANDLE handle = nullptr;
    
    wchar_t converted_file_name[256] = {0};
    for (int i = 0; i < lenght; i++)
    {
        converted_file_name[i] = file_name[i];
    }

    UNICODE_STRING name_obj = {0};
    name_obj.Length = lenght;
    name_obj.MaximumLength = 256;
    name_obj.Buffer = converted_file_name;

    OBJECT_ATTRIBUTES attrs_struct = {0};
    /*
    typedef struct _OBJECT_ATTRIBUTES {
        ULONG Length; -- set to sizeof(struct)
        HANDLE RootDirectory; -- nullptr
        PUNICODE_STRING ObjectName; -- name of the file / device
        ULONG Attributes; -- 0
        PVOID SecurityDescriptor; nullptr // Points to type SECURITY_DESCRIPTOR
        PVOID SecurityQualityOfService; | // Points to type SECURITY_QUALITY_OF_SERVICE
    } OBJECT_ATTRIBUTES;
    */
    InitializeObjectAttributes(&attrs_struct, &name_obj, OBJ_CASE_INSENSITIVE, 0, 0);

    /* return structure
    typedef struct _IO_STATUS_BLOCK {
        union {
            NTSTATUS Status;
            PVOID Pointer;
        } DUMMYUNIONNAME;
        ULONG_PTR Information;
    } IO_STATUS_BLOCK, *PIO_STATUS_BLOCK;
    */

    /*
    HANDLE handle = 
    CreateFileA(
        "CONOUT$", // file name
        FILE_GENERIC_READ | FILE_GENERIC_WRITE, // desired access
        3, // share mode
        nullptr, // security attributes
        3, // creation disposition
        0, // flags and attributes
        nullptr // template file
    );
    */

    // change the name to CONOUT$
    // int error = NtCreateFile(
    //     &handle, // File Handle -- return
    //     FILE_GENERIC_READ | FILE_GENERIC_WRITE, // Desired Access
    //     &attrs_struct, // Object Attributes -- need to mess with
    //     &status_block, // IO Status Block -- return ??
    //     0, // Allocation Size (can be zero if file is being open)
    //     0, // File Attributes (only when created, superseeded or overwritten)
    //     3, // Share Access
    //     3, // Creation Disposition 
    //     0, // Create Options (options when creating or opening a file)
    //     nullptr, // Ea Buffer -- defaults
    //     0 // Ea Buffer Len --  defaults
    // );

    IO_STATUS_BLOCK iosb;
    int error = NtCreateFile(
        &handle, // File Handle -- return
        GENERIC_ALL, // Desired Access
        &attrs_struct, // Object Attributes -- need to mess with
        &iosb, // IO Status Block -- return ??
        0, // Allocation Size (can be zero if file is being open)
        FILE_ATTRIBUTE_NORMAL, // File Attributes (only when created, superseeded or overwritten)
        3, // Share Access
        3, // Creation Disposition 
        FILE_OPEN_BY_FILE_ID | FILE_NON_DIRECTORY_FILE, // Create Options (options when creating or opening a file)
        nullptr, // Ea Buffer -- defaults
        0 // Ea Buffer Len --  defaults
    );

    puts("");
    if (NT_SUCCESS(error))
    {
        puts("succeded execution of NtCreateFile");
    }
    if (NT_ERROR(error))
    {
        printf("error: <%u>\n", error);
    }
    if (NT_INFORMATION(error))
    {
        puts("information on NtCreateFile");
    }
    if (NT_WARNING(error))
    {
        puts("warning on NtCreateFile");
    }
    puts("");
    
    return handle;
}

bool WriteFileP(void * handle, void * buffer, int len, int & written, LPOVERLAPPED overlapped)
{
    (void)overlapped;
    IO_STATUS_BLOCK status_block;

    int ret_code = NtWriteFileP(handle, nullptr, nullptr, nullptr, &status_block, buffer, len, 0, 0);
    written = status_block.Information;

    return NT_SUCCESS(ret_code);
}

int main()
{
    int value = GENERIC_READ | GENERIC_WRITE;
    HANDLE handle =
    // CreateFileA("CONOUT$", value, 3, nullptr, 3, 0, nullptr);
    // CreateFilePP("CONOUT$");
    CreateFilePP("\\??E:\\localhost\\Desktop\\gits\\size_test\\sandbox\\file.data");
    // CreateFileA("E:\\localhost\\Desktop\\gits\\size_test\\sandbox\\file.data", value, 3, nullptr, 3, 0, nullptr);
    
    printf("%i\n", value);

    char str[] = "THE TEXT I WANT TO WRITE\n\n";
    int len = strlen(str);

    print_error();

    DWORD another = 0;
    if (!WriteFile(handle, str, len, &another, nullptr))
    {
        puts("did't worked");
        print_error();
    }

    int written = 0;
    if (!WriteFileP(handle, str, len, written, nullptr))
    {
        puts("didn't work, mine\n");
    }
    else
    {
        puts("worked !!!\n\n\n");
    }

    if (len != written)
    {
        puts("wrong shit");
        printf("%i %i %i\n", len, written, another);
    }

    LARGE_INTEGER num = {0};
    LARGE_INTEGER qan = {0};
    if (!QueryPerformanceCounter( &num ))
    {
        puts("performance counter fail");
    }
    printf("%u\n%i\n", num.QuadPart, qan.QuadPart);

    puts("");

    LARGE_INTEGER number = {0};
    if (!normal_func(&number))
    {
        puts("normal_func failed");
    }
    printf("%u\n", number.QuadPart);

    LARGE_INTEGER sequence = {0};
    if (NtQueryPerformanceCounter(&sequence, &number) != 0)
    {
        puts("NtQueryPerformanceCounter didn't work");
    }
    printf("%u\n", sequence.QuadPart);
}