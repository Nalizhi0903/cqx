#include <stdio.h>
#include <signal.h>
#include <unistd.h>

struct sigaction oldact; 

void sigcallback(int num)
{
    printf("i am sigcallback, signal : %d\n", num);
    sigaction(2, &oldact, NULL);
}

int main()
{
    struct sigaction act;
    act.sa_handler = sigcallback;
    sigemptyset(&act.sa_mask);
    sigaction(2, &act, &oldact);
    while(1)
    {
        sleep(1);
    }
    return 0;
}
