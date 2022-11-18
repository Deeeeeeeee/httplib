#include "aprsock.h"
#include <sys/socket.h>
#include <unistd.h>

int apr_socket(int family, int type, int protocol)
{
    return socket(family, type, protocol);
}

int apr_connect(int fd, const struct sockaddr *addr, socklen_t addrlen)
{
    return connect(fd, addr, addrlen);
}

int apr_close(int socket_fd)
{
    return close(socket_fd);
}

int apr_bind(int fd, const struct sockaddr *addr, socklen_t addrlen)
{
    return bind(fd, addr, addrlen);
}

int apr_listen(int fd, int backlog)
{
    return listen(fd, backlog);
}

int apr_accept(int fd, struct sockaddr * addr, socklen_t * addrlen)
{
    return accept(fd, addr, addrlen);
}
