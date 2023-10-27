#include <unistd.h>
#include "thread_pool.hpp"
using namespace std;

void fun(int data)
{
    printf("data is %d\n", data);
}

int main()
{
   ThreadPool* tp = new ThreadPool(2); 
   if(tp == NULL)
   {
       return 0;
   }
   if(tp->OnInit() <= 0)
   {
       return 0;
   }
   for(int i = 0; i < 10000; i++)
   {
       QueueData qd(i, fun);
       tp->Push(qd);
   }
   while(1)
   {
       sleep(1);
   }
   return 0;
}
