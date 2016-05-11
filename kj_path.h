// `kj_path.h`
// public domain - no offered or implied warranty, use at your own risk

#ifndef KJ_PATH_H
#define KJ_PATH_H

#define KJ_PATH_VERSION_MAJOR 0
#define KJ_PATH_VERSION_MINOR 1
#define KJ_PATH_VERSION_PATCH 0

#if defined(__cplusplus)
extern "C" {
#endif

KJ_API const char* kj_path_extension(const char* path);

#if defined(__cplusplus)
}
#endif

#endif

#if defined(KJ_PATH_IMPL)

const char* kj_path_extension(const char* path) {
    const char* res = NULL;
    if(path) {
        isize size = kj_str_size(path);
        if(size > 3) {
            for(isize i = size - 1; i >= 0; i--) {
                if(path[i] == KJ_PATH_SEPARATOR) {
                    res = NULL;
                    break;
                } elif(path[i] == '.' &&
                       i > 0 &&
                       path[i - 1] != KJ_PATH_SEPARATOR) {
                        res = &path[i + 1];
                    break;
                }
            }
        }
    }
    return res;
}

#endif
