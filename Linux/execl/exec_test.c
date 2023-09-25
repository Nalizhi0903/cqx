#include <stdio.h>
#include <unistd.h>
int main()
{
    printf("start execl\n");
    //extern char** environ;//获得环境变量   三种方法，main函数的参赛，getenv(), exern char** environ
    //execle("/usr/bin/ls", "ls", "-a", "-l", NULL, environ);//带e，需要传递环境变量
    //execlp("ls", "ls", "-a", "-l", NULL);//execlp可以不带路径,函数会在环境变量内path搜索
    //execl("/usr/bin/ls", "ls", "-a", "-l", NULL);//可变参数列表
    //execl("/usr/bin/pwd", "pwd", NULL);
    char* argv[10];
    argv[0] = "ls";
    argv[1] = "-a";
    argv[2] = "-l";
    argv[3] = NULL;
    execv("/usr/bin/ls", argv);//execv,需传递指针数组变量
    printf("faile\n");
    return 0;
}
