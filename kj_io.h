#ifndef KJ_IO_H
#define KJ_IO_H

#if defined(__cplusplus)
extern "C" {
#endif

typedef enum kj_io_err {
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
} kj_io_err_t;

typedef enum kj_io_flag {
    KJ_IO_FLAG_INVALID = (0 << 0),
    KJ_IO_FLAG_READ = (1 << 0),
    KJ_IO_FLAG_WRITE = (1 << 1),
    KJ_IO_FLAG_RDWR = KJ_IO_FLAG_READ | KJ_IO_FLAG_WRITE,
    KJ_IO_FLAG_CREATE = (1 << 2),
    KJ_IO_FLAG_CREATE_NEW = (1 << 3),
    KJ_IO_FLAG_APPEND = (1 << 4),
    KJ_IO_FLAG_TRUNCATE = (1 << 5)
} kj_io_flag_t;

typedef struct kj_io kj_io_t;

kj_api kj_io_t kj_io_open(const char* path, u32 flags);
kj_api kj_io_err_t kj_io_close(kj_io_t* io);
kj_api isize kj_io_read(kj_io_t* io, void* buf, u32 size, u64 offset);
kj_api isize kj_io_write(kj_io_t* io, void* buf, u32 size, u64 offset);

typedef struct kj_io_stat {
    u64 size;
} kj_io_stat_t;

kj_api kj_io_stat_t kj_io_stat(kj_io_t* io);

kj_api const char* kj_io_err_str(kj_io_err_t err);

#if defined(__cplusplus)
}
#endif

#endif

#if defined(KJ_IO_IMPLEMENTATION)

inline const char* kj_io_err_str(kj_io_err_t err)
{
    switch(err) {
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

#include <windows.h>

struct kj_io {
    HANDLE handle;
    u32 flags;
    kj_io_err_t err;
};

internal inline kj_io_err_t kj_io_err_from_win32(u32 err)
{
    switch(err) {
        case ERROR_SUCCESS: return KJ_IO_ERR_NONE;
        case ERROR_ACCESS_DENIED: return KJ_IO_ERR_PERMISSION_DENIED;
        case ERROR_ALREADY_EXISTS: return KJ_IO_ERR_ALREADY_EXISTS;
        case ERROR_BROKEN_PIPE: return KJ_IO_ERR_BROKEN_PIPE;
        case ERROR_FILE_NOT_FOUND: return KJ_IO_ERR_NOT_FOUND;
        case ERROR_PATH_NOT_FOUND: return KJ_IO_ERR_NOT_FOUND;
        case ERROR_NO_DATA: return KJ_IO_ERR_BROKEN_PIPE;
        case ERROR_OPERATION_ABORTED: return KJ_IO_ERR_TIMED_OUT;
        default: return KJ_IO_ERR_UNKNOWN;
    }
}

inline kj_io_t kj_io_open(const char* path, u32 flags)
{
    kj_io_t res;
    u32 access = 0;
    if(flags & KJ_IO_FLAG_READ) {
        access |= GENERIC_READ;
    }
    if(flags & KJ_IO_FLAG_WRITE) {
        access |= GENERIC_WRITE;
    }

    u32 create = OPEN_EXISTING;
    u32 share = FILE_SHARE_READ;
    res.handle = CreateFile(path, access, share, NULL, create, FILE_ATTRIBUTE_NORMAL, NULL);
    res.flags = flags;
    res.err = res.handle == INVALID_HANDLE_VALUE ? KJ_IO_ERR_BAD_HANDLE: kj_io_err_from_errno(errno);
    return res;
}

#elif defined(KJ_SYS_LINUX)

#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

struct kj_io {
    i32 handle;
    u32 flags;
    kj_io_err_t err;
};

internal inline kj_io_err_t kj_io_err_from_errno(u32 err)
{
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

internal inline u32 kj_io_gen_access_mode(u32 flags)
{
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

internal inline u32 kj_io_gen_create_mode(u32 flags)
{
    u32 res = 0;
    if(!(flags & KJ_IO_FLAG_WRITE) && !(flags & KJ_IO_FLAG_APPEND)) {
        if((flags & KJ_IO_FLAG_TRUNCATE) || (flags & KJ_IO_FLAG_CREATE) || (flags & KJ_IO_FLAG_CREATE_NEW)) {
            res = 0;
        }
    } elif(flags & KJ_IO_FLAG_APPEND) {
        if((flags & KJ_IO_FLAG_TRUNCATE) && !(flags & KJ_IO_FLAG_CREATE_NEW)) {
            res = 0;
        }
    } else {
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

kj_io_t kj_io_open(const char* path, u32 flags)
{
    kj_io_t res;
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

kj_io_err_t kj_io_close(kj_io_t* io)
{
    kj_io_err_t res = KJ_IO_ERR_NONE;
    if(close(io->handle) == -1) {
        io->err = kj_io_err_from_errno(errno);
        res = io->err;
    }
    io->handle = -1;
    io->flags = 0;
    return res;
}

isize kj_io_read(kj_io_t* io, void* buf, u32 size, u64 offset)
{
    isize res = -1;
    res = pread(io->handle, buf, size, offset);
    io->err = kj_io_err_from_errno(errno);
    return res;
}

isize kj_io_write(kj_io_t* io, void* buf, u32 size, u64 offset)
{
    isize res = -1;
    res = pwrite(io->handle, buf, size, offset);
    io->err = kj_io_err_from_errno(errno);
    return res;
}

kj_io_stat_t kj_io_stat(kj_io_t* io)
{
    kj_io_stat_t res;
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
