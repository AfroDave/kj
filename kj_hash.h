// `kj_hash.h`
// public domain - no offered or implied warranty, use at your own risk
//
// usage:
//      #define KJ_HASH_IMPL
//      #include "kj_hash.h"

#ifndef KJ_HASH_H
#define KJ_HASH_H

#if defined(__cplusplus)
extern "C" {
#endif

#define KJ_HASH_VERSION_MAJOR 0
#define KJ_HASH_VERSION_MINOR 1
#define KJ_HASH_VERSION_PATCH 0

typedef struct kjHash {
    u32* hash;
    u32 hash_count;
    u32* index;
    u32 index_count;
} kjHash;

KJ_API kjHash kj_hash();
KJ_API u32 kj_hash_str_n(const char* s, isize size);
KJ_API u32 kj_hash_str(const char* s);

#if defined(__cplusplus)
}
#endif

#endif

#if defined(KJ_HASH_IMPL)

kjHash kj_hash() {
    kjHash res;
    res.hash = NULL;
    res.hash_count = 0;
    res.index = NULL;
    res.index_count = 0;
    return res;
}

u32 kj_hash_str_n(const char* s, isize size) {
    u32 res = 0;
    for(isize i = 0; i < size; i++) {
        res += (*s++) * (i + 119);
    }
    return res;
}

u32 kj_hash_str(const char* s) {
    return kj_hash_str_n(s, kj_str_size(s));
}

#endif
