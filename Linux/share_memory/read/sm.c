#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
int main()
{
    //int shmget(key_t key, size_t size, int shmflg);
    //int shmat(int shm_id, const void* shmaddr, int shmflag);
    //int shmdt(const void* shmaddr);
    
    //创建
    int shm_id = shmget(0x78978978, 1024, IPC_CREAT |0664);
    if(shm_id < 0)
    {
        perror("shmget");
        return 0;
    }
    printf("shm_id : %d\n", shm_id);
    //附加
    void* addr = shmat(shm_id,NULL,0);
    if(addr == 0)
    {
        perror("shmat");
        return 0;
    }
    
    while(1)
    {
        printf("%s\n", (char*)addr);
    }
    return 0;   

}
