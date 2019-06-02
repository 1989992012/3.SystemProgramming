/*************************************************************************
	> File Name: tcp.c
	> Author: 
	> Mail: 
	> Created Time: 2019年04月13日 星期六 14时12分59秒
 ************************************************************************/

#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pwd.h>

#ifdef _DEBUG
#define DBG(fmt, args...) printf(fmt, ##args) 
#else 
#define DBG(fmt, args...) 
#endif

int socket_connect(int port, char *host) {
	int sockfd;
	struct sockaddr_in dest_addr;
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket() error");
		return -1;
	}

	memset(&dest_addr, 0, sizeof(dest_addr));//0是把每一个字节都变成0
	dest_addr.sin_family = AF_INET;
	dest_addr.sin_port = htons(port);//本地字节序转化网络字节序
	dest_addr.sin_addr.s_addr = inet_addr(host);//ipv4是32位无符号整型

    DBG("Connetion TO %s:%d\n",host,port);
	fflush(stdout);//标准输出 stdin标准输入 stder标准删除
	if (connect(sockfd, (struct sockaddr *)&dest_addr, sizeof(dest_addr)) < 0) {//从原来开的口直接去连，一个文件对应一个套接字
		//perror("connect() error");//DEBUG关不掉等同于下一句
		DBG("connect() error : %s!\n", stderror(errno)); //返回错误的字符串
		return -1;
	}
	return sockfd;//返回已经建立连接的套接字描述符

}

int main() {
	int  socket_fd;
	struct passwd *pwd;
    pwd = getpwuid(getuid());
	char ip_addr[20] = "192.168.2.88";//结尾可以是结束符，最小值15
	int port = 9999;
    char username[20] = {0};//初始化位0每个字节长度全部为0
    //memset(username, 0, sizeof(username));
    strcpy(username, pwd->pw_name);//->指针 除了strcpy给变量赋值还有sprintf
	socket_fd = socket_connect(port, ip_addr);
    send(socket_fd, username, strlen(username), 0);//由socket函数返回socket_fd套接字描述符 strlen判断username的长度，不能用sizeof固定20个字节长度
	close(socket_fd);//关闭的是socket_fd链接由tcp协议四次挥手
	return 0;

}
