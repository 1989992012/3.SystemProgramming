/*************************************************************************
	> File Name: zuoye1.c
	> Author: liuyan
	> Mail:1989992012@qq.com
	> Created Time: 2019年04月23日 星期二 18时14分42秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <unistd.h>
#include <string.h>

int main(void) {
    struct passwd *pwd;
    pwd = getpwuid(getuid());
    char hostname[32 + 1];
    gethostname(hostname, sizeof(hostname)); 
    char buf[80]; 
    getcwd(buf,sizeof(buf)); 
    printf("\033[36m%s@%s:%s\033[1m\n", pwd->pw_name, hostname, buf);
    return 0;
}

