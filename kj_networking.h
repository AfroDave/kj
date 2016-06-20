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
#include <winsock2.h>
#include <ws2tcpip.h>
#elif defined(KJ_SYS_LINUX)
#include <netinet/in.h>
#else
#error Unsupported Operating System
#endif

typedef struct kjTcpSocket {
#if defined(KJ_SYS_WIN32)
    SOCKET handle;
#elif defined(KJ_SYS_LINUX)
    i32 handle;
#endif
    struct sockaddr_in addr;
    kjErr err;
} kjTcpSocket;

typedef enum kjSocketAddr {
    KJ_SOCKET_ADDR_V4,
    KJ_SOCKET_ADDR_V6,
} kjSocketAddr;

KJ_API b32 kj_networking_begin(void);
KJ_API void kj_networking_end(void);
KJ_API kjErr kj_tcp_socket_open(kjTcpSocket* sock, kjSocketAddr addr);
KJ_API void kj_tcp_socket_close(kjTcpSocket* sock);
KJ_API kjErr kj_tcp_socket_connect(kjTcpSocket* sock, const char* ip, u16 port);
KJ_API kjErr kj_tcp_socket_bind(kjTcpSocket* sock, u16 port, b32 local);
KJ_API isize kj_tcp_socket_read(kjTcpSocket* sock, void* buf, isize size);
KJ_API isize kj_tcp_socket_write(kjTcpSocket* sock, void* buf, isize size);

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

kjErr kj_tcp_socket_open(kjTcpSocket* sock, kjSocketAddr addr) {
    kj_assert(sock);

    kjErr res = KJ_ERR_NONE;
    kj_zero(sock, kj_isize_of(kjTcpSocket));
    i32 type = addr == KJ_SOCKET_ADDR_V4 ? AF_INET: AF_INET6;
    if((sock->handle = socket(
                    type, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) {
        res = kj_networking_err_from_sys();
        sock->err = res;
    }
    return res;
}

void kj_tcp_socket_close(kjTcpSocket* sock) {
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

kjErr kj_tcp_socket_connect(kjTcpSocket* sock, const char* ip, u16 port) {
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
        sock->err = res;
        kj_tcp_socket_close(sock);
    }
    return res;
}

kjErr kj_tcp_socket_bind(kjTcpSocket* sock, u16 port, b32 local) {
    kj_assert(sock);

    kjErr res = KJ_ERR_NONE;
    sock->addr.sin_family = AF_INET;
    sock->addr.sin_addr.s_addr = htonl(local ? INADDR_LOOPBACK: INADDR_ANY);
    sock->addr.sin_port = htons(port);
    if(bind(sock->handle,
                kj_cast(struct sockaddr*, &sock->addr),
                kj_isize_of(struct sockaddr_in)) == SOCKET_ERROR) {
        res = kj_networking_err_from_sys();
        sock->err = res;
        kj_tcp_socket_close(sock);
    }
    return res;
}

isize kj_tcp_socket_read(kjTcpSocket* sock, void* buf, isize size) {
    kj_assert(sock);

    isize res = -1;
    res = recv(sock->handle, buf, size, 0);
    return res;
}

isize kj_tcp_socket_write(kjTcpSocket* sock, void* buf, isize size) {
    kj_assert(sock);

    isize res = -1;
    res = send(sock->handle, buf, size, 0);
    return res;
}

#endif
