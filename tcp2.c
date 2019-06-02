/*************************************************************************
	> File Name: tcp2.c
	> Author: liuyan
	> Mail:1989992012@qq.com
	> Created Time: 2019年06月01日 星期六 15时33分29秒
 ************************************************************************/

#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pwd.h>

int main() {

    int sockfd;
    int new_sockfd;
    char buf[1024] = {0};
    int port = 8888;
    struct sockaddr_in my_addr, peer_addr;
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket()");
        return 1;
    }
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(port);
    my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if ((bind(sockfd, (struct sockaddr *)&my_addr, sizeof(my_addr))) < 0) {
        perror("bind()");
        return 1;
    }

    pid_t pid;
    int x = 0;
    for (int i = 0; i <= 2; i++) {
        fork();
        if (pid == 0) break;
        x = i;
        printf("%d", x);

    }
    if (listen(sockfd, 20) < 0) {
        perror("listen()");
        return 1;
    }
    socklen_t len = sizeof(struct sockaddr);
    if ((new_sockfd = accept(sockfd, (struct sockaddr *)&peer_addr, &len)) < 0) {
            perror("accept()");
            return 1;
    }
    if (recv(new_sockfd, buf, sizeof(buf), 0) > 0) {
        printf("%s:%s\n", buf, inet_ntoa(peer_addr.sin_addr));
    }
    close(new_sockfd);
    close(sockfd);
    
    
    return 0;
}

