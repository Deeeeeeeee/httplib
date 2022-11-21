#include "write.h"
#include <errno.h>
#include <stddef.h>
#include <sys/types.h>
#include <unistd.h>

ssize_t writen(int fd, const void *vptr, size_t n)
{
    size_t nleft;                   // 剩下多少字节要写
    ssize_t nwritten;               // 写了多少字节
    const char *ptr;                // 临时指针

    ptr = vptr;
    nleft = n;
    while(nleft > 0) {
        if ( (nwritten = write(fd, ptr, nleft)) <= 0) {
            if (nwritten < 0 && errno == EINTR)
                nwritten = 0;       // 重新调
            else
                return(-1);         // 异常
        }

        nleft -= nwritten;
        ptr += nwritten;
    }

    return(n);
}
