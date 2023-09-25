#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(){
    pid_t ret = fork();
    if(ret < 0){
        return 0;
    }else if(ret == 0){
        //child
        sleep(2);
        printf("i am child..., %d , %d\n", getpid(), getppid());
        exit(1);
    }else{
        //father
        int status;
        while(waitpid(ret, &status, WNOHANG)==0) 
        {
            printf("still waitting\n");
        }

        if((status & 0x7f) > 0){
            //异常
            printf("异常退出：signal is %d, coredump flag %d\n", status & 0x7f, (status >> 7) & 0x1);
        }else{
            //正常
            printf("正常退出： return code is %d\n", (status >> 8) & 0xFF);
        }
    }
    return 0;
}
