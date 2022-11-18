#include <sys/socket.h>

int apr_socket(int family, int type, int protocol);

int apr_connect(int fd, const struct sockaddr *addr, socklen_t addrlen);

int apr_close(int socket_fd);

int apr_bind(int fd, const struct sockaddr *addr, socklen_t addrlen);

int apr_listen(int fd, int backlog);

int apr_accept(int fd, struct sockaddr * addr, socklen_t * addrlen);
