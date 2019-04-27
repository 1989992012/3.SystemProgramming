/*************************************************************************
	> File Name: test.c
	> Author: liuyan
	> Mail:1989992012@qq.com
	> Created Time: 2019年04月27日 星期六 18时46分18秒
 ************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>

int main(int argc, char *argv[]) {
    printf("argv[0] = %s\n", argv[0] + 2); 
    printf("argv[1] = %s\n", argv[1]);
    printf("argv[2] = %s\n", argv[2]);
    printf("argc = %d\n", argc);
    struct stat st;
    if (stat(argv[1], &st) < 0) {
        perror("stat");
    }
    printf("%d\t%d\t%d\t%d\t%d\t\t%s\n", st.st_mode, st.st_nlink, st.st_uid, st.st_gid, st.st_size, argv[1]);
    return 0;
}
