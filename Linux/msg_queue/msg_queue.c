#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>
#include <unistd.h>

struct msgbuf 
{
    long mtype;
    char mtext[512];
};

int main()
{
    //int msgget(key_t key, int msgflg);
    //int msgsnd(int msqid, const void* msgp, size_t msgsz, int msgflg);
    //ssize_t msgrcv(int msqid, void* msgp, size_t msgsz, long msgtyp, int msgflg);
    int q_id = msgget(0x1234567, IPC_CREAT);
    if(q_id < 0)
    {
        perror("msgget");
        return 0;
    }
    printf("q_id : %d\n", q_id);
    struct msgbuf mb;
    mb.mtype = 1;
    strcpy(mb.mtext, "x");
    msgsnd(q_id, &mb, sizeof(mb.mtext), IPC_NOWAIT);
    return 0;
}
