// `kj_io.h`
// public domain - no offered or implied warranty, use at your own risk

#ifndef KJ_IO_H
#define KJ_IO_H

#define KJ_IO_VERSION_MAJOR 0
#define KJ_IO_VERSION_MINOR 2
#define KJ_IO_VERSION_PATCH 1

#define KJ_ERR_BAD_HANDLE 1
#define KJ_ERR_PERMISSION_DENIED 2
#define KJ_ERR_NOT_FOUND 3
#define KJ_ERR_BROKEN_PIPE 4
#define KJ_ERR_ALREADY_EXISTS 5
#define KJ_ERR_TIMED_OUT 6
#define KJ_ERR_INVALID_INPUT 7
#define KJ_ERR_INTERRUPED 8
#define KJ_ERR_ILLEGAL_SEEK 9

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
    void* handle;
    u32 flags;
    kjErr err;
} kjIo;
#elif defined(KJ_SYS_LINUX)
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
typedef struct kjIo {
    i32 handle;
    u32 flags;
    kjErr err;
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

#define kj_io_has_err(io) ((io)->err != KJ_ERR_NONE)

KJ_API kjIo kj_io_open(const char* path, u32 flags);
KJ_API kjErr kj_io_close(kjIo* io);
KJ_API isize kj_io_read(kjIo* io, void* buf, isize size);
KJ_API isize kj_io_write(kjIo* io, void* buf, isize size);
KJ_API isize kj_io_read_at(kjIo* io, void* buf, isize size, i64 offset);
KJ_API isize kj_io_write_at(kjIo* io, void* buf, isize size, i64 offset);

KJ_API kjIoStat kj_io_stat(kjIo* io);

//KJ_API isize kj_io_name(kjIo* io, char* buf, isize size);

KJ_API const char* kj_io_err_str(kjIo* io);

#if defined(__cplusplus)
}
#endif

#endif

#if defined(KJ_IO_IMPL)

const char* kj_io_err_str(kjIo* io) {
    switch(io->err) {
        case KJ_ERR_NONE: return "None";
        case KJ_ERR_BAD_HANDLE: return "Bad Handle";
        case KJ_ERR_PERMISSION_DENIED: return "Permission Denied";
        case KJ_ERR_NOT_FOUND: return "Not Found";
        case KJ_ERR_BROKEN_PIPE: return "Broken Pipe";
        case KJ_ERR_ALREADY_EXISTS: return "Already Exists";
        case KJ_ERR_TIMED_OUT: return "Timed Out";
        case KJ_ERR_INVALID_INPUT: return "Invalid Input";
        case KJ_ERR_INTERRUPED: return "Interrupted";
        case KJ_ERR_ILLEGAL_SEEK: return "Illegal Seek";
        default: return "Unknown";
    }
}

#if defined(KJ_SYS_WIN32)

kj_internal kjErr kj_io_err_from_sys(u32 err) {
    switch(err) {
        case ERROR_SUCCESS: return KJ_ERR_NONE;
        case ERROR_ACCESS_DENIED: return KJ_ERR_PERMISSION_DENIED;
        case ERROR_ALREADY_EXISTS: return KJ_ERR_ALREADY_EXISTS;
        case ERROR_BROKEN_PIPE: return KJ_ERR_BROKEN_PIPE;
        case ERROR_FILE_NOT_FOUND: return KJ_ERR_NOT_FOUND;
        case ERROR_PATH_NOT_FOUND: return KJ_ERR_NOT_FOUND;
        case ERROR_NO_DATA: return KJ_ERR_BROKEN_PIPE;
        case ERROR_INVALID_PARAMETER: return KJ_ERR_INVALID_INPUT;
        case ERROR_OPERATION_ABORTED: return KJ_ERR_TIMED_OUT;
        case ERROR_SEEK: return KJ_ERR_ILLEGAL_SEEK;
        case ERROR_NEGATIVE_SEEK: return KJ_ERR_ILLEGAL_SEEK;
        case ERROR_SEEK_ON_DEVICE: return KJ_ERR_ILLEGAL_SEEK;
        default: return KJ_ERR_UNKNOWN;
    }
}

kj_internal u32 kj_io_gen_access_mode(u32 flags) {
    u32 res = 0;
    if((flags & KJ_IO_FLAG_READ) &&
      !(flags & KJ_IO_FLAG_WRITE) &&
      !(flags & KJ_IO_FLAG_APPEND)) {
        res = GENERIC_READ;
    } elif(!(flags & KJ_IO_FLAG_READ) &&
            (flags & KJ_IO_FLAG_WRITE) &&
           !(flags & KJ_IO_FLAG_APPEND)) {
        res = GENERIC_WRITE;
    } elif((flags & KJ_IO_FLAG_READ) &&
           (flags & KJ_IO_FLAG_WRITE) &&
          !(flags & KJ_IO_FLAG_APPEND)) {
        res = GENERIC_READ | GENERIC_WRITE;
    } elif(!(flags & KJ_IO_FLAG_READ) &&
            (flags & KJ_IO_FLAG_APPEND)) {
        res = FILE_GENERIC_WRITE & ~FILE_WRITE_DATA;
    } elif((flags & KJ_IO_FLAG_READ) &&
           (flags & KJ_IO_FLAG_APPEND)) {
        res = GENERIC_READ | (FILE_GENERIC_WRITE & ~FILE_WRITE_DATA);
    }
    return res;
}

kj_internal u32 kj_io_gen_create_mode(u32 flags) {
    u32 res = 0;
    if(!(flags & KJ_IO_FLAG_WRITE) &&
       !(flags & KJ_IO_FLAG_APPEND)) {
        if((flags & KJ_IO_FLAG_TRUNCATE) ||
           (flags & KJ_IO_FLAG_CREATE) ||
           (flags & KJ_IO_FLAG_CREATE_NEW)) {
            res = U32_MAX;
        }
    } elif(flags & KJ_IO_FLAG_APPEND) {
        if((flags & KJ_IO_FLAG_TRUNCATE) &&
          !(flags & KJ_IO_FLAG_CREATE_NEW)) {
            res = U32_MAX;
        }
    }
    if(res == 0) {
        if(!(flags & KJ_IO_FLAG_CREATE) &&
           !(flags & KJ_IO_FLAG_TRUNCATE) &&
           !(flags & KJ_IO_FLAG_CREATE_NEW)) {
            res = OPEN_EXISTING;
        } elif((flags & KJ_IO_FLAG_CREATE) &&
              !(flags & KJ_IO_FLAG_TRUNCATE) &&
              !(flags & KJ_IO_FLAG_CREATE_NEW)) {
            res = OPEN_ALWAYS;
        } elif(!(flags & KJ_IO_FLAG_CREATE) &&
                (flags & KJ_IO_FLAG_TRUNCATE) &&
               !(flags & KJ_IO_FLAG_CREATE_NEW)) {
            res = TRUNCATE_EXISTING;
        } elif((flags & KJ_IO_FLAG_CREATE) &&
               (flags & KJ_IO_FLAG_TRUNCATE) &&
              !(flags & KJ_IO_FLAG_CREATE_NEW)) {
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
    if((access | create) == U32_MAX) {
        res.handle = NULL;
        res.flags = 0;
        res.err = KJ_ERR_INVALID_INPUT;
    } else {
        res.handle = CreateFile(
                path, access,
                FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
                NULL, create, 0, NULL);
        res.flags = flags;
        res.err = res.handle == INVALID_HANDLE_VALUE ? KJ_ERR_BAD_HANDLE:
            kj_io_err_from_sys(GetLastError());
    }
    return res;
}

kjErr kj_io_close(kjIo* io) {
    kjErr res = KJ_ERR_NONE;
    if(!CloseHandle(io->handle)) {
        res = kj_io_err_from_sys(GetLastError());
    }
    io->handle = NULL;
    return res;
}

isize kj_io_read(kjIo* io, void* buf, isize size) {
    isize res = -1;
    DWORD read = 0;
    if(ReadFile(
        io->handle, buf, kj_cast(DWORD, size),
        kj_cast(DWORD*, &read), NULL)) {
        res = read;
    } else {
        io->err = kj_io_err_from_sys(GetLastError());
    }
    return res;
}

isize kj_io_write(kjIo* io, void* buf, isize size) {
    isize res = -1;
    DWORD wrote = 0;
    if(WriteFile(
        io->handle, buf, kj_cast(DWORD, size),
        kj_cast(DWORD*, &wrote), NULL)) {
        res = wrote;
    } else {
        io->err = kj_io_err_from_sys(GetLastError());
    }
    return res;
}

isize kj_io_read_at(kjIo* io, void* buf, isize size, i64 offset) {
    isize res = -1;
    OVERLAPPED overlapped = {0};
    overlapped.Offset = kj_cast(u32, ((offset >> 0) & 0xFFFFFFFF));
    overlapped.OffsetHigh = kj_cast(u32, ((offset >> 32) & 0xFFFFFFFF));
    DWORD read = 0;
    if(ReadFile(
        io->handle, buf, kj_cast(DWORD, size),
        kj_cast(DWORD*, &read), &overlapped)) {
        res = read;
    } else {
        io->err = kj_io_err_from_sys(GetLastError());
    }
    return res;
}

isize kj_io_write_at(kjIo* io, void* buf, isize size, i64 offset) {
    isize res = -1;
    OVERLAPPED overlapped = {0};
    overlapped.Offset = kj_cast(u32, ((offset >> 0) & 0xFFFFFFFF));
    overlapped.OffsetHigh = kj_cast(u32, ((offset >> 32) & 0xFFFFFFFF));
    DWORD wrote = 0;
    if(WriteFile(
        io->handle, buf, kj_cast(DWORD, size),
        kj_cast(DWORD*, &wrote), &overlapped)) {
        res = wrote;
    } else {
        io->err = kj_io_err_from_sys(GetLastError());
    }
    return res;
}

kjIoStat kj_io_stat(kjIo* io) {
    kjIoStat res = {0};
    BY_HANDLE_FILE_INFORMATION io_info = {0};
    if(GetFileInformationByHandle(io->handle, &io_info)) {
        res.size = (kj_cast(i64, io_info.nFileSizeHigh) << 32) |
                    kj_cast(i64, io_info.nFileSizeLow);
    } else {
        io->err = kj_io_err_from_sys(GetLastError());
    }
    return res;
}

#elif defined(KJ_SYS_LINUX)

kj_internal kjErr kj_io_err_from_sys(u32 err) {
    switch(err) {
        case 0: return KJ_ERR_NONE;
        case EBADF: return KJ_ERR_BAD_HANDLE;
        case EPERM: return KJ_ERR_PERMISSION_DENIED;
        case EACCES: return KJ_ERR_PERMISSION_DENIED;
        case EEXIST: return KJ_ERR_ALREADY_EXISTS;
        case EPIPE: return KJ_ERR_BROKEN_PIPE;
        case ENOENT: return KJ_ERR_NOT_FOUND;
        case ETIMEDOUT: return KJ_ERR_TIMED_OUT;
        case EINVAL: return KJ_ERR_INVALID_INPUT;
        case EINTR: return KJ_ERR_INTERRUPED;
        case ESPIPE: return KJ_ERR_ILLEGAL_SEEK;
        default: return KJ_ERR_UNKNOWN;
    }
}

kj_internal u32 kj_io_gen_access_mode(u32 flags) {
    u32 res = 0;
    if((flags & KJ_IO_FLAG_READ) &&
      !(flags & KJ_IO_FLAG_WRITE) &&
      !(flags & KJ_IO_FLAG_APPEND)) {
        res = O_RDONLY;
    } elif(!(flags & KJ_IO_FLAG_READ) &&
            (flags & KJ_IO_FLAG_WRITE) &&
           !(flags & KJ_IO_FLAG_APPEND)) {
        res = O_WRONLY;
    } elif((flags & KJ_IO_FLAG_READ) &&
           (flags & KJ_IO_FLAG_WRITE) &&
          !(flags & KJ_IO_FLAG_APPEND)) {
        res = O_RDWR;
    } elif(!(flags & KJ_IO_FLAG_READ) &&
            (flags & KJ_IO_FLAG_APPEND)) {
        res = O_WRONLY | O_APPEND;
    } elif((flags & KJ_IO_FLAG_READ) &&
           (flags & KJ_IO_FLAG_APPEND)) {
        res = O_RDWR | O_APPEND;
    }
    return res;
}

kj_internal u32 kj_io_gen_create_mode(u32 flags) {
    u32 res = 0;
    if(!(flags & KJ_IO_FLAG_WRITE) &&
       !(flags & KJ_IO_FLAG_APPEND)) {
        if((flags & KJ_IO_FLAG_TRUNCATE) ||
           (flags & KJ_IO_FLAG_CREATE) ||
           (flags & KJ_IO_FLAG_CREATE_NEW)) {
            res = U32_MAX;
        }
    } elif(flags & KJ_IO_FLAG_APPEND) {
        if((flags & KJ_IO_FLAG_TRUNCATE) &&
          !(flags & KJ_IO_FLAG_CREATE_NEW)) {
            res = U32_MAX;
        }
    }
    if(res == 0) {
        if((flags & KJ_IO_FLAG_CREATE) &&
          !(flags & KJ_IO_FLAG_TRUNCATE) &&
          !(flags & KJ_IO_FLAG_CREATE_NEW)) {
            res = O_CREAT;
        } elif(!(flags & KJ_IO_FLAG_CREATE) &&
                (flags & KJ_IO_FLAG_TRUNCATE) &&
               !(flags & KJ_IO_FLAG_CREATE_NEW)) {
            res = O_TRUNC;
        } elif((flags & KJ_IO_FLAG_CREATE) &&
               (flags & KJ_IO_FLAG_TRUNCATE) &&
              !(flags & KJ_IO_FLAG_CREATE_NEW)) {
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
    if((access | create) == U32_MAX) {
        res.handle = -1;
        res.flags = 0;
        res.err = KJ_ERR_INVALID_INPUT;
    } else {
        u32 perm = 0666;
        kj_syscall3(KJ_SYSCALL_OPEN, res.handle, path, (access | create), perm);
        res.flags = flags;
        res.err = kj_io_err_from_sys(res.handle < 0 ? -res.handle: 0);
    }
    return res;
}

kjErr kj_io_close(kjIo* io) {
    kjErr res = KJ_ERR_NONE;
    i32 out = 0;
    kj_syscall1(KJ_SYSCALL_CLOSE, out, io->handle);
    if(out < 0) {
        res = kj_io_err_from_sys(out < 0 ? -out: 0);
    }
    io->handle = -1;
    io->flags = 0;
    io->err = res;
    return res;
}

isize kj_io_read(kjIo* io, void* buf, isize size) {
    isize res = -1;
    kj_syscall3(KJ_SYSCALL_READ, res, io->handle, buf, size);
    io->err = kj_io_err_from_sys(res < 0 ? -res: 0);
    return res;
}

isize kj_io_write(kjIo* io, void* buf, isize size) {
    isize res = -1;
    kj_syscall3(KJ_SYSCALL_WRITE, res, io->handle, buf, size);
    io->err = kj_io_err_from_sys(res < 0 ? -res: 0);
    return res;
}

isize kj_io_read_at(kjIo* io, void* buf, isize size, i64 offset) {
    isize res = -1;
    kj_syscall4(KJ_SYSCALL_PREAD, res, io->handle, buf, size, offset);
    io->err = kj_io_err_from_sys(res < 0 ? -res: 0);
    return res;
}

isize kj_io_write_at(kjIo* io, void* buf, isize size, i64 offset) {
    isize res = -1;
    kj_syscall4(KJ_SYSCALL_PWRITE, res, io->handle, buf, size, offset);
    io->err = kj_io_err_from_sys(res < 0 ? -res: 0);
    return res;
}

kjIoStat kj_io_stat(kjIo* io) {
    kjIoStat res;
    struct stat buf;
    if(fstat(io->handle, &buf) == -1) {
        io->err = kj_io_err_from_sys(errno);
        res.size = 0;
    } else {
        res.size = buf.st_size;
    }
    return res;
}

isize kj_io_name(kjIo* io, char* buf, isize size) {
    isize res = -1;
    static char path[256] = {0};
    kj_snprintf(path, kj_isize_of(path), "/proc/self/fd/%d", io->handle);
    kj_syscall3(KJ_SYSCALL_READLINK, res, path, buf, size);
    io->err = kj_io_err_from_sys(res < 0 ? -res: 0);
    return res;
}

#else
#error KJ_IO_UNSUPPORTED
#endif
#endif
