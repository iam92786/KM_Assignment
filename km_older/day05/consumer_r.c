#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/shm.h>

void consumer(int sig);
int shmid;
char *msg;

void main()
{
    shmid = shmget(10, 1024, 0666);
    if (shmid == -1)
    {
        perror("Shared memory error!");
        exit(0);
    }

    (void)signal(SIGUSR1, consumer);
    kill(getppid(), SIGUSR2);
    while (1)
    {
        pause();
    }
}

void consumer(int sig)
{
    int out = 0;
    char data[26];
    int y = 26;
    msg = shmat(shmid, 0, 0);
    while (y > 0)
    {
        data[out] = msg[out];
        out = (out + 1) % 26;
        if (out == 0)
        {
            printf("\t c:%s\n", data);
            sleep(1);
        }
        y--;
    }
    shmdt(msg);
    kill(getppid(), SIGUSR2);
}