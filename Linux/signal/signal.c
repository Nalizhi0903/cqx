#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
int main()
{
    int* ptr = (int*)malloc(1024);
    free(ptr);
    free(ptr);
    //char Arr[1];
    //Arr[12] = 'x';

   return 0;
}
