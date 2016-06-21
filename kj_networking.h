// `kj_networking.h`
// public domain - no warranty implied; use at your own risk
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
    kjErr err;
} kjSocket;

typedef enum kjSocketAddr {
    KJ_SOCKET_ADDR_V4,
    KJ_SOCKET_ADDR_V6,
} kjSocketAddr;

KJ_API b32 kj_networking_begin(void);
KJ_API void kj_networking_end(void);
KJ_API kjErr kj_socket_open(kjSocket* sock, kjSocketAddr addr);
KJ_API void kj_socket_close(kjSocket* sock);
KJ_API kjErr kj_socket_connect(kjSocket* sock, const char* ip, u16 port);
KJ_API kjErr kj_socket_bind(kjSocket* sock, u16 port, b32 local);
KJ_API kjErr kj_socket_listen(kjSocket* sock, i32 max_conn);
KJ_API kjErr kj_socket_accept(kjSocket* sock, kjSocket* client);
KJ_API isize kj_socket_read(kjSocket* sock, void* buf, isize size);
KJ_API isize kj_socket_write(kjSocket* sock, const void* buf, isize size);

KJ_EXTERN_END

#endif

#if defined(KJ_NETWORKING_IMPL)

#if defined(KJ_SYS_WIN32)
KJ_INTERN kjErr kj_networking_err_from_sys(void) {
    i32 err = WSAGetLastError();
    switch(err) {
        case 0: return KJ_ERR_NONE;
        case WSAEBADF: return KJ_ERR_BAD_HANDLE;
        case WSAEACCES: return KJ_ERR_PERMISSION_DENIED;
        case WSAETIMEDOUT: return KJ_ERR_TIMED_OUT;
        case WSAEINVAL: return KJ_ERR_INVALID_INPUT;
        case WSAEINTR: return KJ_ERR_INTERRUPED;
        case WSAEADDRINUSE: return KJ_ERR_ADDR_IN_USE;
        case WSAEADDRNOTAVAIL: return KJ_ERR_ADDR_NOT_AVAILABLE;
        case WSAECONNABORTED: return KJ_ERR_CONNECTION_ABORTED;
        case WSAECONNREFUSED: return KJ_ERR_CONNECTION_REFUSED;
        case WSAECONNRESET: return KJ_ERR_CONNECTION_RESET;
        case WSAENOTCONN: return KJ_ERR_NOT_CONNECTED;
        case WSAEWOULDBLOCK: return KJ_ERR_WOULD_BLOCK;
        default: return KJ_ERR_UNKNOWN;
    }
}
#elif defined(KJ_SYS_LINUX)
#include <arpa/inet.h>
#include <unistd.h>

#define INVALID_SOCKET (-1)
#define SOCKET_ERROR (-1)

KJ_INTERN kjErr kj_networking_err_from_sys(void) {
    i32 err = errno;
    switch(err) {
        case 0: return KJ_ERR_NONE;
        case EBADF: return KJ_ERR_BAD_HANDLE;
        case EACCES: return KJ_ERR_PERMISSION_DENIED;
        case ETIMEDOUT: return KJ_ERR_TIMED_OUT;
        case EINVAL: return KJ_ERR_INVALID_INPUT;
        case EINTR: return KJ_ERR_INTERRUPED;
        case EADDRINUSE: return KJ_ERR_ADDR_IN_USE;
        case EADDRNOTAVAIL: return KJ_ERR_ADDR_NOT_AVAILABLE;
        case ECONNABORTED: return KJ_ERR_CONNECTION_ABORTED;
        case ECONNREFUSED: return KJ_ERR_CONNECTION_REFUSED;
        case ECONNRESET: return KJ_ERR_CONNECTION_RESET;
        case ENOTCONN: return KJ_ERR_NOT_CONNECTED;
        case EWOULDBLOCK: return KJ_ERR_WOULD_BLOCK;
        case EAGAIN: return KJ_ERR_WOULD_BLOCK;
        default: return KJ_ERR_UNKNOWN;
    }
}
#endif

b32 kj_networking_begin(void) {
    b32 res = false;
#if defined(KJ_SYS_WIN32)
    WSADATA wsa;
    if(WSAStartup(0x202, &wsa) == NO_ERROR) {
        res = true;
    }
#elif defined(KJ_SYS_LINUX)
    res = true;
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
    kj_assert(sock);

    kjErr res = KJ_ERR_NONE;
    kj_zero(sock, kj_isize_of(kjSocket));
    i32 type = addr == KJ_SOCKET_ADDR_V4 ? AF_INET: AF_INET6;
    if((sock->handle = socket(
                    type, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) {
        res = kj_networking_err_from_sys();
    }
    sock->err = res;
    return res;
}

void kj_socket_close(kjSocket* sock) {
    kj_assert(sock);

    if(sock->handle != INVALID_SOCKET) {
#if defined(KJ_SYS_WIN32)
        closesocket(sock->handle);
#elif defined(KJ_SYS_LINUX)
        close(sock->handle);
#endif
        sock->handle = INVALID_SOCKET;
    }
}

kjErr kj_socket_connect(kjSocket* sock, const char* ip, u16 port) {
    kj_assert(sock);

    kjErr res = KJ_ERR_NONE;
    kj_zero(&sock->addr, kj_isize_of(struct sockaddr_in));
    sock->addr.sin_family = AF_INET;
    sock->addr.sin_addr.s_addr = inet_addr(ip);
    sock->addr.sin_port = htons(port);

    if(connect(sock->handle,
                kj_cast(struct sockaddr*, &sock->addr),
                kj_isize_of(struct sockaddr_in)) == SOCKET_ERROR) {
        res = kj_networking_err_from_sys();
        kj_socket_close(sock);
    }
    sock->err = res;
    return res;
}

kjErr kj_socket_bind(kjSocket* sock, u16 port, b32 local) {
    kj_assert(sock);

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
        res = kj_networking_err_from_sys();
        kj_socket_close(sock);
    }
    sock->err = res;
    return res;
}

kjErr kj_socket_listen(kjSocket* sock, i32 max_conn) {
    kj_assert(sock);

    kjErr res = KJ_ERR_NONE;
    if(listen(sock->handle, kj_min(max_conn, SOMAXCONN)) == SOCKET_ERROR) {
        res = kj_networking_err_from_sys();
        kj_socket_close(sock);
    }
    sock->err = res;
    return res;
}

kjErr kj_socket_accept(kjSocket* sock, kjSocket* client) {
    kj_assert(sock);
    kj_assert(client);

    kjErr res = KJ_ERR_NONE;
    SOCKET s;
    if((s = accept(sock->handle, NULL, NULL)) == SOCKET_ERROR) {
        res = kj_networking_err_from_sys();
        kj_socket_close(sock);
    } else {
        kj_zero(client, kj_isize_of(kjSocket));
        client->handle = s;
    }
    sock->err = res;
    return res;
}

isize kj_socket_read(kjSocket* sock, void* buf, isize size) {
    kj_assert(sock);

    isize res = -1;
    res = recv(
            sock->handle,
            buf,
#if defined(KJ_SYS_WIN32)
            kj_cast(i32, size),
#elif defined(KJ_SYS_LINUX)
            size,
#endif
            0);
    return res;
}

isize kj_socket_write(kjSocket* sock, const void* buf, isize size) {
    kj_assert(sock);

    isize res = -1;
    res = send(
            sock->handle,
            buf,
#if defined(KJ_SYS_WIN32)
            kj_cast(i32, size),
#elif defined(KJ_SYS_LINUX)
            size,
#endif
            0);
    return res;
}

#endif
