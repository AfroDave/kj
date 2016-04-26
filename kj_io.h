#ifndef KJ_IO_H
#define KJ_IO_H

#define KJ_IO_VERSION_MAJOR 0
#define KJ_IO_VERSION_MINOR 1
#define KJ_IO_VERSION_PATCH 0

typedef enum kjIoErr {
    KJ_IO_ERR_NONE,
    KJ_IO_ERR_BAD_HANDLE,
    KJ_IO_ERR_PERMISSION_DENIED,
    KJ_IO_ERR_NOT_FOUND,
    KJ_IO_ERR_BROKEN_PIPE,
    KJ_IO_ERR_ALREADY_EXISTS,
    KJ_IO_ERR_TIMED_OUT,
    KJ_IO_ERR_INVALID_INPUT,
    KJ_IO_ERR_INTERRUPED,
    KJ_IO_ERR_UNKNOWN,
    KJ_IO_ERR_COUNT
} kjIoErr;

typedef enum kjIoFlag {
    KJ_IO_FLAG_INVALID = (0 << 0),
    KJ_IO_FLAG_READ = (1 << 0),
    KJ_IO_FLAG_WRITE = (1 << 1),
    KJ_IO_FLAG_RDWR = KJ_IO_FLAG_READ | KJ_IO_FLAG_WRITE,
    KJ_IO_FLAG_CREATE = (1 << 2),
    KJ_IO_FLAG_CREATE_NEW = (1 << 3),
    KJ_IO_FLAG_APPEND = (1 << 4),
    KJ_IO_FLAG_TRUNCATE = (1 << 5)
} kjIoFlag;

#if defined(KJ_SYS_WIN32)
#include <windows.h>
typedef struct kjIo {
    HANDLE handle;
    u32 flags;
    kjIoErr err;
} kjIo;
#elif defined(KJ_SYS_LINUX)
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
typedef struct kjIo {
    i32 handle;
    u32 flags;
    kjIoErr err;
} kjIo;
#else
#error KJ_IO_UNSUPPORTED
#endif

typedef struct kjIoStat {
    i64 size;
} kjIoStat;

#if defined(__cplusplus)
extern "C" {
#endif

#define kj_io_has_err(io) ((io)->err != KJ_IO_ERR_NONE)

KJ_API kjIo kj_io_open(const char* path, u32 flags);
KJ_API kjIoErr kj_io_close(kjIo* io);
KJ_API isize kj_io_read(kjIo* io, void* buf, isize size, i64 offset);
KJ_API isize kj_io_write(kjIo* io, void* buf, isize size, i64 offset);

KJ_API kjIoStat kj_io_stat(kjIo* io);

KJ_API const char* kj_io_err_str(kjIo* io);

#if defined(__cplusplus)
}
#endif

#endif

#if defined(KJ_IO_IMPLEMENTATION)

const char* kj_io_err_str(kjIo* io) {
    switch(io->err) {
        case KJ_IO_ERR_NONE: return "None";
        case KJ_IO_ERR_BAD_HANDLE: return "Bad Handle";
        case KJ_IO_ERR_PERMISSION_DENIED: return "Permission Denied";
        case KJ_IO_ERR_NOT_FOUND: return "Not Found";
        case KJ_IO_ERR_BROKEN_PIPE: return "Broken Pipe";
        case KJ_IO_ERR_ALREADY_EXISTS: return "Already Exists";
        case KJ_IO_ERR_TIMED_OUT: return "Timed Out";
        case KJ_IO_ERR_INVALID_INPUT: return "Invalid Input";
        case KJ_IO_ERR_INTERRUPED: return "Interrupted";
        default: return "Unknown";
    }
}

#if defined(KJ_SYS_WIN32)

internal kjIoErr kj_io_err_from_win32(u32 err) {
    switch(err) {
        case ERROR_SUCCESS: return KJ_IO_ERR_NONE;
        case ERROR_ACCESS_DENIED: return KJ_IO_ERR_PERMISSION_DENIED;
        case ERROR_ALREADY_EXISTS: return KJ_IO_ERR_ALREADY_EXISTS;
        case ERROR_BROKEN_PIPE: return KJ_IO_ERR_BROKEN_PIPE;
        case ERROR_FILE_NOT_FOUND: return KJ_IO_ERR_NOT_FOUND;
        case ERROR_PATH_NOT_FOUND: return KJ_IO_ERR_NOT_FOUND;
        case ERROR_NO_DATA: return KJ_IO_ERR_BROKEN_PIPE;
        case ERROR_INVALID_PARAMETER: return KJ_IO_ERR_INVALID_INPUT;
        case ERROR_OPERATION_ABORTED: return KJ_IO_ERR_TIMED_OUT;
        default: return KJ_IO_ERR_UNKNOWN;
    }
}

internal u32 kj_io_gen_access_mode(u32 flags) {
    u32 res = 0;
    if((flags & KJ_IO_FLAG_READ) && !(flags & KJ_IO_FLAG_WRITE) && !(flags & KJ_IO_FLAG_APPEND)) {
        res = GENERIC_READ;
    } elif(!(flags & KJ_IO_FLAG_READ) && (flags & KJ_IO_FLAG_WRITE) && !(flags & KJ_IO_FLAG_APPEND)) {
        res = GENERIC_WRITE;
    } elif((flags & KJ_IO_FLAG_READ) && (flags & KJ_IO_FLAG_WRITE) && !(flags & KJ_IO_FLAG_APPEND)) {
        res = GENERIC_READ | GENERIC_WRITE;
    } elif(!(flags & KJ_IO_FLAG_READ) && (flags & KJ_IO_FLAG_APPEND)) {
        res = FILE_GENERIC_WRITE & ~FILE_WRITE_DATA;
    } elif((flags & KJ_IO_FLAG_READ) && (flags & KJ_IO_FLAG_APPEND)) {
        res = GENERIC_READ | (FILE_GENERIC_WRITE & ~FILE_WRITE_DATA);
    }
    return res;
}

internal u32 kj_io_gen_create_mode(u32 flags) {
    u32 res = U32_MAX;
    if(!(flags & KJ_IO_FLAG_WRITE) && !(flags & KJ_IO_FLAG_APPEND)) {
        if((flags & KJ_IO_FLAG_TRUNCATE) || (flags & KJ_IO_FLAG_CREATE) || (flags & KJ_IO_FLAG_CREATE_NEW)) {
            res = 0;
        }
    } elif(flags & KJ_IO_FLAG_APPEND) {
        if((flags & KJ_IO_FLAG_TRUNCATE) && !(flags & KJ_IO_FLAG_CREATE_NEW)) {
            res = 0;
        }
    }
    if(res != 0) {
        if(!(flags & KJ_IO_FLAG_CREATE) && !(flags & KJ_IO_FLAG_TRUNCATE) && !(flags & KJ_IO_FLAG_CREATE_NEW)) {
            res = OPEN_EXISTING;
        } elif((flags & KJ_IO_FLAG_CREATE) && !(flags & KJ_IO_FLAG_TRUNCATE) && !(flags & KJ_IO_FLAG_CREATE_NEW)) {
            res = OPEN_ALWAYS;
        } elif(!(flags & KJ_IO_FLAG_CREATE) && (flags & KJ_IO_FLAG_TRUNCATE) && !(flags & KJ_IO_FLAG_CREATE_NEW)) {
            res = TRUNCATE_EXISTING;
        } elif((flags & KJ_IO_FLAG_CREATE) && (flags & KJ_IO_FLAG_TRUNCATE) && !(flags & KJ_IO_FLAG_CREATE_NEW)) {
            res = CREATE_ALWAYS;
        } elif(flags & KJ_IO_FLAG_CREATE_NEW) {
            res = CREATE_NEW;
        }
    }
    return res;
}

kjIo kj_io_open(const char* path, u32 flags) {
    kjIo res;
    u32 access = kj_io_gen_access_mode(flags);
    u32 create = kj_io_gen_create_mode(flags);
    res.handle = CreateFile(path, access, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, NULL, create, 0, NULL);
    res.flags = flags;
    res.err = res.handle == INVALID_HANDLE_VALUE ? KJ_IO_ERR_BAD_HANDLE: kj_io_err_from_win32(GetLastError());
    return res;
}

kjIoErr kj_io_close(kjIo* io) {
    kjIoErr res = KJ_IO_ERR_NONE;
    if(!CloseHandle(io->handle)) {
        res = kj_io_err_from_win32(GetLastError());
    }
    io->handle = NULL;
    return res;
}

isize kj_io_read(kjIo* io, void* buf, isize size, i64 offset) {
    isize res = -1;
    OVERLAPPED overlapped = {0};
    overlapped.Offset = cast_of(u32, ((offset >> 0) & 0xFFFFFFFF));
    overlapped.OffsetHigh = cast_of(u32, ((offset >> 32) & 0xFFFFFFFF));
    DWORD read = 0;
    if(ReadFile(io->handle, buf, cast_of(DWORD, size), cast_of(DWORD*, &read), &overlapped)) {
        res = read;
    } else {
        io->err = kj_io_err_from_win32(GetLastError());
    }
    return res;
}

isize kj_io_write(kjIo* io, void* buf, isize size, i64 offset) {
    isize res = -1;
    OVERLAPPED overlapped = {0};
    overlapped.Offset = cast_of(u32, ((offset >> 0) & 0xFFFFFFFF));
    overlapped.OffsetHigh = cast_of(u32, ((offset >> 32) & 0xFFFFFFFF));
    DWORD wrote = 0;
    if(WriteFile(io->handle, buf, cast_of(DWORD, size), cast_of(DWORD*, &wrote), &overlapped)) {
        res = wrote;
    } else {
        io->err = kj_io_err_from_win32(GetLastError());
    }
    return res;
}

kjIoStat kj_io_stat(kjIo* io) {
    kjIoStat res = {0};
    BY_HANDLE_FILE_INFORMATION io_info = {0};
    if(GetFileInformationByHandle(io->handle, &io_info)) {
        res.size = (cast_of(i64, io_info.nFileSizeHigh) << 32) | cast_of(i64, io_info.nFileSizeLow);
    } else {
        io->err = kj_io_err_from_win32(GetLastError());
    }
    return res;
}

#elif defined(KJ_SYS_LINUX)

internal kjIoErr kj_io_err_from_errno(u32 err) {
    switch(err) {
        case 0: return KJ_IO_ERR_NONE;
        case EBADF: return KJ_IO_ERR_BAD_HANDLE;
        case EPERM: return KJ_IO_ERR_PERMISSION_DENIED;
        case EACCES: return KJ_IO_ERR_PERMISSION_DENIED;
        case EEXIST: return KJ_IO_ERR_ALREADY_EXISTS;
        case EPIPE: return KJ_IO_ERR_BROKEN_PIPE;
        case ENOENT: return KJ_IO_ERR_NOT_FOUND;
        case ETIMEDOUT: return KJ_IO_ERR_TIMED_OUT;
        case EINVAL: return KJ_IO_ERR_INVALID_INPUT;
        case EINTR: return KJ_IO_ERR_INTERRUPED;
        default: return KJ_IO_ERR_UNKNOWN;
    }
}

internal u32 kj_io_gen_access_mode(u32 flags) {
    u32 res = 0;
    if((flags & KJ_IO_FLAG_READ) && !(flags & KJ_IO_FLAG_WRITE) && !(flags & KJ_IO_FLAG_APPEND)) {
        res = O_RDONLY;
    } elif(!(flags & KJ_IO_FLAG_READ) && (flags & KJ_IO_FLAG_WRITE) && !(flags & KJ_IO_FLAG_APPEND)) {
        res = O_WRONLY;
    } elif((flags & KJ_IO_FLAG_READ) && (flags & KJ_IO_FLAG_WRITE) && !(flags & KJ_IO_FLAG_APPEND)) {
        res = O_RDWR;
    } elif(!(flags & KJ_IO_FLAG_READ) && (flags & KJ_IO_FLAG_APPEND)) {
        res = O_WRONLY | O_APPEND;
    } elif((flags & KJ_IO_FLAG_READ) && (flags & KJ_IO_FLAG_APPEND)) {
        res = O_RDWR | O_APPEND;
    }
    return res;
}

internal u32 kj_io_gen_create_mode(u32 flags) {
    u32 res = U32_MAX;
    if(!(flags & KJ_IO_FLAG_WRITE) && !(flags & KJ_IO_FLAG_APPEND)) {
        if((flags & KJ_IO_FLAG_TRUNCATE) || (flags & KJ_IO_FLAG_CREATE) || (flags & KJ_IO_FLAG_CREATE_NEW)) {
            res = 0;
        }
    } elif(flags & KJ_IO_FLAG_APPEND) {
        if((flags & KJ_IO_FLAG_TRUNCATE) && !(flags & KJ_IO_FLAG_CREATE_NEW)) {
            res = 0;
        }
    }
    if(res != 0) {
        if((flags & KJ_IO_FLAG_CREATE) && !(flags & KJ_IO_FLAG_TRUNCATE) && !(flags & KJ_IO_FLAG_CREATE_NEW)) {
            res = O_CREAT;
        } elif(!(flags & KJ_IO_FLAG_CREATE) && (flags & KJ_IO_FLAG_TRUNCATE) && !(flags & KJ_IO_FLAG_CREATE_NEW)) {
            res = O_TRUNC;
        } elif((flags & KJ_IO_FLAG_CREATE) && (flags & KJ_IO_FLAG_TRUNCATE) && !(flags & KJ_IO_FLAG_CREATE_NEW)) {
            res = O_CREAT | O_TRUNC;
        } elif(flags & KJ_IO_FLAG_CREATE_NEW) {
            res = O_CREAT | O_EXCL;
        }
    }
    return res;
}

kjIo kj_io_open(const char* path, u32 flags) {
    kjIo res;
    u32 access = kj_io_gen_access_mode(flags);
    u32 create = kj_io_gen_create_mode(flags);
    if((access | create) == 0) {
        res.handle = -1;
        res.flags = 0;
        res.err = KJ_IO_ERR_INVALID_INPUT;
    } else {
        u32 permissions = 0666;
        res.handle = open(path, access | create, permissions);
        res.flags = flags;
        res.err = res.handle == -1 ? KJ_IO_ERR_BAD_HANDLE: kj_io_err_from_errno(errno);
    }
    return res;
}

kjIoErr kj_io_close(kjIo* io) {
    kjIoErr res = KJ_IO_ERR_NONE;
    if(close(io->handle) == -1) {
        io->err = kj_io_err_from_errno(errno);
        res = io->err;
    }
    io->handle = -1;
    io->flags = 0;
    return res;
}

isize kj_io_read(kjIo* io, void* buf, isize size, i64 offset) {
    isize res = -1;
#if defined(KJ_ARCH_64_BIT)
    register i64 r10 __asm("r10") = offset;
    __asm volatile(
        "syscall"
        : "=a" (res)
        : "0" (17), "D" (io->handle), "S" (buf), "d" (size), "r" (r10));
#elif define(KJ_ARCH_32_BIT)
    __asm volatile(
        "int $0x80"
        : "=a" (res)
        : "0" (180), "b" (io->handle), "c" (buf), "d" (size), "s" (offset));
#else
#error KJ_IO_READ_UNSUPPORTED
#endif
    io->err = kj_io_err_from_errno(errno);
    return res;
}

isize kj_io_write(kjIo* io, void* buf, isize size, i64 offset) {
    isize res = -1;
#if defined(KJ_ARCH_64_BIT)
    register i64 r10 __asm("r10") = offset;
    __asm volatile(
        "syscall"
        : "=a" (res)
        : "0" (18), "D" (io->handle), "S" (buf), "d" (size), "r" (r10));
#elif define(KJ_ARCH_32_BIT)
    __asm volatile(
        "int $0x80"
        : "=a" (res)
        : "0" (181), "b" (io->handle), "c" (buf), "d" (size), "s" (offset));
#else
#error KJ_IO_WRITE_UNSUPPORTED
#endif
    io->err = kj_io_err_from_errno(errno);
    return res;
}

kjIoStat kj_io_stat(kjIo* io) {
    kjIoStat res;
    struct stat buf;
    if(fstat(io->handle, &buf) == -1) {
        io->err = kj_io_err_from_errno(errno);
        res.size = 0;
    } else {
        res.size = buf.st_size;
    }
    return res;
}

#else
#error KJ_IO_UNSUPPORTED
#endif
#endif
