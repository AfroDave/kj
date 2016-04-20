#ifndef KJ_IO_H
#define KJ_IO_H

typedef enum kj_io_err {
    KJ_IO_ERR_NONE,
    KJ_IO_ERR_UNKNOWN,
    KJ_IO_ERR_COUNT,
} kj_io_err_t;

typedef enum kj_io_flag {
    KJ_IO_FLAG_NONE = (0 << 0),
    KJ_IO_FLAG_READ = (1 << 0),
    KJ_IO_FLAG_WRITE = (1 << 1),
} kj_io_flag_t;

typedef struct kj_io kj_io_t;

kj_api kj_io_t kj_io_open(const char* path, u32 flags);

#endif

#if defined(KJ_IO_IMPLEMENTATION)

#if defined(KJ_SYS_WIN32)

struct kj_io {
    HANDLE handle;
    u32 flags;
    kj_io_err_t err;
};

kj_io_t kj_io_err_from_win32_err(u32 err)
{
    return err == 0 ? KJ_IO_ERR_NONE: KJ_IO_ERR_UNKNOWN;
}

kj_io_t kj_io_open(const char* path, u32 flags)
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
    res.err = res.handle != INVALID_HANDLE_VALUE ? KJ_ERR_NONE: kj_io_err_from_win32_err(GetLastError());
    return res;
}

#else
struct kj_io {
    i32 handle;
    u32 flags;
    kj_io_err_t err;
};
#error KJ_IO_UNSUPPORTED
#endif

#endif
