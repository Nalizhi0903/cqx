#include <stdio.h>
#include <signal.h>
volatile int is_quit = 1;//保证内存可见性，不管优先级，变量必须从内存中读取，而不是寄存器，保证变量稳定
void sigcallback(int sig)
{
    printf("sig is %d\n", sig);
    is_quit = 0;
}
int main()
{
    signal(2, sigcallback);
    while(is_quit){}//若不加volatile且设置优先级，判断循环读取is_quit是从寄存器中读取
    return 0;
}
