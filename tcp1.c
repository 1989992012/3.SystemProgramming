/*************************************************************************
	> File Name: tcp1.c
mZ> Author: liuyan
	> Mail:1989992012@qq.com
	> Created Time: 2019年05月31日 星期五 19时54分54秒
 ************************************************************************/

#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pwd.h>
#include <signal.h>
#include <sys/wait.h>

#ifdef _DEBUG
#define DBG(fmt, args...) printf(fmt, ##args) 
#else 
#define DBG(fmt, args...) 
#endif

void SignalFun() {//2
    int status;  //2
    wait(&status);//2
}

int main() {
    int sockfd, new_sock;
	pid_t pid;
    struct sockaddr_in my_addr, peer_addr;
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket()");
        return 1;
    }
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(9999);
	my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(my_addr))) {
        perror("bind()");
        return 1;
    }
    if(listen(sockfd, 20) < 0) {
        perror("listen()");
        return 1;
    }
    socklen_t len = sizeof(struct sockaddr);
    while (1) {
        if ((new_sock = accept(sockfd, (struct sockaddr *)&peer_addr, &len)) < 0) {
            perror("accpect()");
            return 1;
        }
        signal(14, SignalFun);    //2
        pid = fork();
        if (pid > 0) {
        //    int status;
            close(new_sock);
        //    wait(&status);
            continue;
        }
        //pid_t pid_s;
        //pid_s = fork();
        //if (pid_s > 0) exit(0);

        pid_t ppid = getppid(); //2
        close(sockfd);
        char buff[1024] = {0};
        if (recv(new_sock, buff, sizeof(buff), 0) > 0) {
            printf("%s:%s\n", buff, inet_ntoa(peer_addr.sin_addr));
        }
        close(new_sock);
        kill(ppid, 14);  //2
        exit(0);
    }

	return 0;
}	
