#include <stdio.h>
#include <signal.h>
#include <unistd.h>
void sigcallback(int sig)
{
    printf("i am sigcallbacl fun, sig : %d\n", sig);
}

int main()
{
    signal(2, sigcallback);
    while(1)
    {
        sleep(1);
    }
    return 0;
}
