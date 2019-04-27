/*************************************************************************
	> File Name: test2.c
	> Author: liuyan
	> Mail:1989992012@qq.com
	> Created Time: 2019年04月27日 星期六 20时13分00秒
 ************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#define PATH "./" 

int main(void) {
    DIR *p_dir = NULL; 
    p_dir = opendir(PATH); 
    if (NULL == p_dir) 
    {
        perror("opendir");
        exit(0);
    }
    char *p_name;
    struct dirent *d_dir = NULL;
    struct stat st; 
    memset(&st,0,sizeof(st));
    while (d_dir = readdir(p_dir)) {
        if ('.' == *(d_dir->d_name))
            continue;
        p_name = d_dir->d_name;
    stat(p_name,&st);

    int n_size,n_link;
    n_link = st.st_nlink;
    n_size = st.st_size;

#if 1
    char n_dir;
    if (S_ISREG(st.st_mode))
        n_dir = '-';
    else if (S_ISDIR(st.st_mode))//判断是否为目录类型
        n_dir = 'd';
    else if (S_ISCHR(st.st_mode))//判断是否为chr类型
        n_dir = 'c';
    else if (S_ISBLK(st.st_mode))//判断是否为块设备类型
        n_dir = 'b';
    else if (S_ISFIFO(st.st_mode))//判断是否为管道类型
        n_dir = 'p';
    else if (S_ISLNK(st.st_mode))//判断是否为软链接类型
        n_dir = 'l';
    else if (S_ISSOCK(st.st_mode))//判断是否为套接字类型
        n_dir = 's';
    else
        n_dir = '?';//如果都不是，用?表示无法识别
#endif
#if 1
    char n_power[10] = {};
    if (S_IRUSR & st.st_mode)
        n_power[0] = 'r';
    else
        n_power[0] = '-';
    if (S_IWUSR & st.st_mode)//判断用户位是否可写
        n_power[1] = 'w';
    else
        n_power[1] = '-';
    if (S_IXUSR & st.st_mode)//判断用户位是否可执行
        n_power[2] = 'x';
    else
        n_power[2] = '-';
    if (S_IRGRP & st.st_mode)//判断用户组位是否可读
        n_power[3] = 'r';
    else
        n_power[3] = '-';
    if (S_IWGRP & st.st_mode)//判断用户组位是否可写
        n_power[4] = 'w';
    else
        n_power[4] = '-';
    if (S_IXGRP & st.st_mode)//判断用户组位是否可执行
        n_power[5] = 'x';
    else
        n_power[5] = '-';
    if (S_IROTH & st.st_mode)//判断其他用户是否可读
        n_power[6] = 'r';
    else
        n_power[6] = '-';
    if (S_IWOTH & st.st_mode)//判断其他用户是否可写
        n_power[7] = 'w';
    else
        n_power[7] = '-';
    if (S_IXOTH & st.st_mode)//判断其他用户是否可执行
        n_power[8] = 'x';
    else
        n_power[8] = '-';
#endif
#if 1
    struct passwd *u_uid = NULL;
    u_uid = getpwuid(st.st_uid);
    if (NULL == u_uid)//判断u_uid指针是否指向成功
    {
        perror("getpwuid");
        exit(0);
    }
    char *g_uid = u_uid->pw_name;//定义char*型指针g_uid用来保存得到的用户名
#endif
#if 1
    struct group *gr_gid = NULL;//定义getgrgid结构体指针gr_gid,并初始化为空
    gr_gid = getgrgid(st.st_gid);
    if (NULL == gr_gid)//判断gr_gid指针是否指向成功
    {
        perror("getgrgid");
        exit(0);
    }
    char *g_gid = gr_gid->gr_name;//定义char*型指针g_gid用来保存得到的组名
#endif

#if 1
    struct tm *local_time = NULL;
    local_time = localtime(&st.st_ctime);

    if (NULL == local_time) //判断local_time指针是否绑定成功
    {
        perror("localtime");
        exit(0);
    }
    int n_num = local_time->tm_mon;
    char *n_mon;//定义char*型变来嗯n_mon，用来转换数字月份到英文简写月份
    int n_day = local_time->tm_mday;
    int n_hour = local_time->tm_hour;
    int n_min = local_time->tm_min;
    switch (n_num)//利用switch-case语句用来转换数字月份到英文简写月份
    {
        case 0:
            n_mon = "Jan";
            break;
        case 1:
            n_mon = "Feb";
            break;
        case 2:
            n_mon = "Mar";
            break;
        case 3:
            n_mon = "Apr";
            break;
        case 4:
            n_mon = "May";
            break;
        case 5:
            n_mon = "Jun";
            break;
        case 6:
            n_mon = "Jul";
            break;
        case 7:
            n_mon = "Aug";
            break;
        case 8:
            n_mon = "Sep";
            break;
        case 9:
            n_mon = "Otc";
            break;
        case 10:
            n_mon = "Nov";
            break;
        case 11:
            n_mon = "Dec";
            break;
        default:
            break;
    }
#endif
    printf("%c%s %d %s %s %d \t %s %d %d:%d\t%s\n",n_dir,n_power,n_link,g_uid,g_gid,n_size,n_mon,n_day,n_hour,n_min,p_name);//输出需要的变量访问结果
    }
    return 0;
}
