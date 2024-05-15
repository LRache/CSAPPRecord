#include <stdio.h>
#include "csapp.h"

/* Recommended max cache and object sizes */
#define MAX_CACHE_SIZE 1049000
#define MAX_OBJECT_SIZE 102400

/* You won't lose style points for including this long line in your code */
static const char *user_agent_hdr = "User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:10.0.3) Gecko/20120305 Firefox/10.0.3\r\n";

void do_proxy(int);

int main(int argc, char **argv)
{
    struct sockaddr_storage *clientAddr;
    int addrSize = sizeof(clientAddr);
    
    int listenfd = Open_listenfd(argv[1]);
    while (1)
    {
        int connectfd = Accept(listenfd, (SA*) clientAddr, &addrSize);
        do_proxy(connectfd);
        close(connectfd);
    }
    
    
    printf("%s", user_agent_hdr);
    return 0;
}

void do_proxy(int fd) {
    char buffer[MAXLINE];
    char method[MAXLINE], url[MAXLINE], version[MAXLINE];
    rio_t connectRio;
    rio_t *connectRp = &connectRio;
    Rio_readinitb(connectRp, fd);

    Rio_readlineb(connectRp, buffer, MAXBUF);
    sscanf(buffer, "%s %s %s", method, url, version);
    
    char host[50], path[100], hostname[50], port[6];
    sscanf(url, "%*[^:]://%49[^/]/%99[^\n]", host, path);
    int n = sscanf(host, "%s:%s", hostname, port);
    int client_fd;
    if (n == 0) return;
    else if (n == 1) {
        client_fd = Open_clientfd(host, "80");
    } else {
        client_fd = Open_clientfd(host, port);
    }

    char request[MAXBUF];
    sprintf(request, "%s %s HTTP/1.0\r\n", method, path);
    sprintf(request, "%s\r\n", request);
    sprintf(request, "%shost: %s\r\n", request, hostname);
    sprintf(request, "%sUser-Agent: %s\r\n", request, user_agent_hdr);
    sprintf(request, "%sConnection: close\r\nProxy-Connection: close\r\n\r\n", request);
    Rio_writen(client_fd, buffer, strlen(buffer));
    while ((n =Rio_readlineb(connectRp, buffer, MAXLINE)) != -1)
    {
        Rio_writen(client_fd, buffer, n);
    }
}
