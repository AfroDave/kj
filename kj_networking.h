// `kj_networking.h`
//
// ---------------------------------- LICENSE ----------------------------------
// This software is in the public domain.  Where that dedication is not
// recognized, you are granted a perpetual, irrevocable license to copy,
// distribute, and modify the source code as you see fit.
//
// The source code is provided "as is", without warranty of any kind, express
// or implied. No attribution is required, but always appreciated.
// =============================================================================
//
// usage:
//      #define KJ_NETWORKING_IMPL
//      #include "kj_networking.h"

#ifndef KJ_NETWORKING_H
#define KJ_NETWORKING_H

#define KJ_NETWORKING_VERSION_MAJOR 0
#define KJ_NETWORKING_VERSION_MINOR 1
#define KJ_NETWORKING_VERSION_PATCH 0

KJ_EXTERN_BEGIN

#if defined(KJ_SYS_WIN32)
#if !defined(_WINSOCK_DEPRECATED_NO_WARNINGS)
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#endif
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "mswsock.lib")
#elif defined(KJ_SYS_LINUX)
#include <netinet/in.h>
#else
#error Unsupported Operating System
#endif

typedef struct kjSocket {
#if defined(KJ_SYS_WIN32)
    SOCKET handle;
#elif defined(KJ_SYS_LINUX)
    i32 handle;
#endif
    struct sockaddr_in addr;
} kjSocket;

typedef enum kjSocketAddr {
    KJ_SOCKET_ADDR_V4,
    KJ_SOCKET_ADDR_V6
} kjSocketAddr;

KJ_API b32 kj_networking_begin(void);
KJ_API void kj_networking_end(void);
KJ_API kjErr kj_socket_open(kjSocket* sock, kjSocketAddr addr);
KJ_API void kj_socket_close(kjSocket* sock);
KJ_API kjErr kj_socket_connect(kjSocket* sock, const char* ip, u16 port);
KJ_API kjErr kj_socket_bind(kjSocket* sock, u16 port, b32 local);
KJ_API kjErr kj_socket_listen(kjSocket* sock, i32 max_conn);
KJ_API kjErr kj_socket_accept(kjSocket* sock, kjSocket* client);
KJ_API isize$ kj_socket_read(kjSocket* sock, void* buf, isize size);
KJ_API isize$ kj_socket_write(kjSocket* sock, const void* buf, isize size);

KJ_EXTERN_END

#endif

#if defined(KJ_NETWORKING_IMPL)

#if defined(KJ_SYS_LINUX)
#include <arpa/inet.h>
#include <unistd.h>
typedef i32 SOCKET;
enum {
    INVALID_SOCKET = -1,
    SOCKET_ERROR = -1
};
#endif

b32 kj_networking_begin(void) {
    b32 res = KJ_FALSE;
#if defined(KJ_SYS_WIN32)
    WSADATA wsa;
    if(WSAStartup(0x202, &wsa) == NO_ERROR) {
        res = KJ_TRUE;
    }
#elif defined(KJ_SYS_LINUX)
    res = KJ_TRUE;
#endif
    return res;
}

void kj_networking_end(void) {
#if defined(KJ_SYS_WIN32)
    WSACleanup();
#elif defined(KJ_SYS_LINUX)
#endif
}

kjErr kj_socket_open(kjSocket* sock, kjSocketAddr addr) {
    if(sock == NULL) {
        return KJ_ERR_INVALID_PARAMETER;
    }

    kjErr res = KJ_ERR_NONE;
    i32 type = addr == KJ_SOCKET_ADDR_V4 ? AF_INET: AF_INET6;
    if((sock->handle = socket(
                    type, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) {
#if defined(KJ_SYS_WIN32)
        res = kj_err_from_sys(WSAGetLastError());
#elif defined(KJ_SYS_LINUX)
        res = kj_err_from_sys(errno);
#endif
    }
    return res;
}

void kj_socket_close(kjSocket* sock) {
    if(sock == NULL || sock->handle == INVALID_SOCKET) {
        return;
    }

#if defined(KJ_SYS_WIN32)
    closesocket(sock->handle);
#elif defined(KJ_SYS_LINUX)
    close(sock->handle);
#endif
}

kjErr kj_socket_connect(kjSocket* sock, const char* ip, u16 port) {
    if(sock == NULL || ip == NULL) {
        return KJ_ERR_INVALID_PARAMETER;
    }

    kjErr res = KJ_ERR_NONE;
    kj_zero(&sock->addr, kj_isize_of(struct sockaddr_in));
    sock->addr.sin_family = AF_INET;
    sock->addr.sin_addr.s_addr = inet_addr(ip);
    sock->addr.sin_port = htons(port);

    if(connect(sock->handle,
                kj_cast(struct sockaddr*, &sock->addr),
                kj_isize_of(struct sockaddr_in)) == SOCKET_ERROR) {
#if defined(KJ_SYS_WIN32)
        res = kj_err_from_sys(WSAGetLastError());
#elif defined(KJ_SYS_LINUX)
        res = kj_err_from_sys(errno);
#endif
        kj_socket_close(sock);
    }
    return res;
}

kjErr kj_socket_bind(kjSocket* sock, u16 port, b32 local) {
    if(sock == NULL || sock->handle == INVALID_SOCKET) {
        return KJ_ERR_INVALID_PARAMETER;
    }

    kjErr res = KJ_ERR_NONE;
    kj_zero(&sock->addr, kj_isize_of(struct sockaddr_in));
    sock->addr.sin_family = AF_INET;
    sock->addr.sin_addr.s_addr = htonl(local ? INADDR_LOOPBACK: INADDR_ANY);
    sock->addr.sin_port = htons(port);
    i32 reuse = 1;
#if defined(KJ_SYS_WIN32)
    setsockopt(
            sock->handle, SOL_SOCKET, SO_REUSEADDR,
            kj_cast(char*, &reuse), kj_isize_of(i32));
    reuse = 1;
    setsockopt(
            sock->handle, SOL_SOCKET, SO_EXCLUSIVEADDRUSE,
            kj_cast(char*, &reuse), kj_isize_of(i32));
#elif defined(KJ_SYS_LINUX)
    setsockopt(
            sock->handle, SOL_SOCKET, SO_REUSEADDR, &reuse, kj_isize_of(i32));
#endif
    if(bind(sock->handle,
                kj_cast(struct sockaddr*, &sock->addr),
                kj_isize_of(struct sockaddr_in)) == SOCKET_ERROR) {
#if defined(KJ_SYS_WIN32)
        res = kj_err_from_sys(WSAGetLastError());
#elif defined(KJ_SYS_LINUX)
        res = kj_err_from_sys(errno);
#endif
        kj_socket_close(sock);
    }
    return res;
}

kjErr kj_socket_listen(kjSocket* sock, i32 max_conn) {
    if(sock == NULL || sock->handle == INVALID_SOCKET || max_conn <= 0) {
        return KJ_ERR_INVALID_PARAMETER;
    }

    kjErr res = KJ_ERR_NONE;
    if(listen(sock->handle, kj_min(max_conn, SOMAXCONN)) == SOCKET_ERROR) {
#if defined(KJ_SYS_WIN32)
        res = kj_err_from_sys(WSAGetLastError());
#elif defined(KJ_SYS_LINUX)
        res = kj_err_from_sys(errno);
#endif
        kj_socket_close(sock);
    }
    return res;
}

kjErr kj_socket_accept(kjSocket* sock, kjSocket* client) {
    if(sock == NULL || sock->handle == INVALID_SOCKET || client == NULL) {
        return KJ_ERR_INVALID_PARAMETER;
    }

    kjErr res = KJ_ERR_NONE;
    SOCKET s;
    if((s = accept(sock->handle, NULL, NULL)) == SOCKET_ERROR) {
#if defined(KJ_SYS_WIN32)
        res = kj_err_from_sys(WSAGetLastError());
#elif defined(KJ_SYS_LINUX)
        res = kj_err_from_sys(errno);
#endif
        kj_socket_close(sock);
    } else {
        kj_zero(client, kj_isize_of(kjSocket));
        client->handle = s;
    }
    return res;
}

isize$ kj_socket_read(kjSocket* sock, void* buf, isize size) {
    isize$ res;
    if(sock == NULL || sock->handle == INVALID_SOCKET ||
       buf == NULL || size <= 0) {
        res.err = KJ_ERR_INVALID_PARAMETER;
        return res;
    };
    kj_zero(&res, kj_isize_of(isize$));

    res.val = recv(
            sock->handle,
#if defined(KJ_SYS_WIN32)
            kj_cast(char*, buf),
            kj_cast(i32, size),
#elif defined(KJ_SYS_LINUX)
            buf,
            size,
#endif
            0);
    if(res.val == SOCKET_ERROR) {
#if defined(KJ_SYS_WIN32)
        res.err = kj_err_from_sys(WSAGetLastError());
#elif defined(KJ_SYS_LINUX)
        res.err = kj_err_from_sys(errno);
#endif
    }
    return res;
}

isize$ kj_socket_write(kjSocket* sock, const void* buf, isize size) {
    isize$ res;
    if(sock == NULL || sock->handle == INVALID_SOCKET ||
       buf == NULL || size <= 0) {
        res.err = KJ_ERR_INVALID_PARAMETER;
        return res;
    }
    kj_zero(&res, kj_isize_of(isize$));

    res.val = send(
            sock->handle,
#if defined(KJ_SYS_WIN32)
            kj_cast(const char*, buf),
            kj_cast(i32, size),
#elif defined(KJ_SYS_LINUX)
            buf,
            size,
#endif
            0);
    if(res.val == SOCKET_ERROR) {
#if defined(KJ_SYS_WIN32)
        res.err = kj_err_from_sys(WSAGetLastError());
#elif defined(KJ_SYS_LINUX)
        res.err = kj_err_from_sys(errno);
#endif
    }
    return res;
}

#endif
