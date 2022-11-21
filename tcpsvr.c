#include "net/aprsock.h"
#include "net/write.h"
#include <strings.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#define MAXLINE 4096

void str_echo(int sockfd);

int main(int argc, char *argv[])
{
    int listenfd, connfd;
    pid_t childpid;
    socklen_t clilen;
    struct sockaddr_in cliaddr, svraddr;

    // socket
    if ( (listenfd = apr_socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("socket fail. errno:%d\n", errno);
        exit(1);
    }

    bzero(&svraddr, sizeof(svraddr));
    svraddr.sin_family = AF_INET;
    svraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    svraddr.sin_port = htons(9987);

    // bind
    if (apr_bind(listenfd, (struct sockaddr *) &svraddr, sizeof(svraddr)) < 0) {
        printf("bind fail. errno:%d\n", errno);
        exit(1);
    }

    // listen
    if (apr_listen(listenfd, 1024) < 0) {
        printf("listen fail. errno:%d\n", errno);
        exit(1);
    }

    for (;;) {
        clilen = sizeof(cliaddr);
        // accept
        if ( (connfd = apr_accept(listenfd, (struct sockaddr *) &cliaddr, &clilen)) < 0) {
            printf("accept fail. errno:%d\n", errno);
            continue;
        }

        if ( (childpid = fork()) == 0) {    // 子进程
            apr_close(listenfd);
            str_echo(connfd);
            exit(0);
        }
        apr_close(connfd);
    }
    return 0;
}

/** void str_echo(int sockfd) */
/** { */
/**     char line[MAXLINE]; */
/**     FILE *fpin, *fpout; */
/**  */
/**     fpin = fdopen(sockfd, "r"); */
/**     fpout = fdopen(sockfd, "w"); */
/**  */
/**     while (fgets(line, MAXLINE, fpin) != NULL) { */
/**         printf("%s", line); */
/**         fputs(line, fpout); */
/**     } */
/** } */

void str_echo(int sockfd)
{
    ssize_t n;
    char buf[MAXLINE];

again:
    while( (n = read(sockfd, buf, MAXLINE)) > 0)
        if (writen(sockfd, buf, n) < 0) {
            printf("write fail. errno:%d\n", errno);
            exit(1);
        }

    printf("%s", buf);

    if (n < 0 && errno == EINTR)
        goto again;
    else if (n < 0)
        printf("str_echo read error. errno:%d\n", errno);
}
