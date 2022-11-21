#include "net/aprsock.h"
#include "net/write.h"
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

#define MAXLINE 4096

char *Fgets(char *ptr, int n, FILE *stream);

int main(int argc, char *argv[])
{
    int sockfd;
    struct sockaddr_in svraddr;

    if (argc != 2) {
        printf("usage: tcpcli <ipaddress>");
        exit(0);
    }

    sockfd = apr_socket(AF_INET, SOCK_STREAM, 0);

    bzero(&svraddr, sizeof(svraddr));
    svraddr.sin_family = AF_INET;
    svraddr.sin_port = htons(9987);
    
    if (inet_pton(AF_INET, argv[1], &svraddr.sin_addr) <= 0) {
        printf("inet_pton fail. errno:%d\n", errno);
        exit(1);
    }

    // connect
    if (apr_connect(sockfd, (struct sockaddr *) &svraddr, sizeof(svraddr)) < 0) {
        printf("connect fail. errno:%d\n", errno);
        exit(1);
    }

    exit(0);
}

void str_cli(FILE *fp, int sockfd)
{
    char sendline[MAXLINE], recvline[MAXLINE];

    while(Fgets(sendline, MAXLINE, fp) != NULL) {

        // 发送
        if (writen(sockfd, sendline, strlen(sendline)) < 0) {
            printf("write fail. errno:%d\n", errno);
            exit(1);
        }

        // 接收

        // 打印

    }
}

char *Fgets(char *ptr, int n, FILE *stream)
{
    char *rptr;     // 返回的指针

    if ( (rptr = fgets(ptr, n, stream)) == NULL && ferror(stream)) {
        printf("fgets fail. errno:%d\n", errno);
        exit(1);
    }

    return (rptr);
}
