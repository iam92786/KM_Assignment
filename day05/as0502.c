/*
Assignment 2:
        Write a producer and consumer problem using fork() and 
    shared memory. Synchronizing producer and consumer process using named semaphores.
*/

#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <string.h>

pid_t pid;
int shmid;
char *msg;
sem_t *empty, *full;

int main()
{
    shmid = shmget(10, 1024, 0666 | IPC_CREAT);
    if (shmid == -1)
    {
        perror("Shared memory error!");
        exit(0);
    }

    full = sem_open("csem", O_CREAT, 0664, 0);

    empty = sem_open("psem", O_CREAT, 0664, 26);

    pid = fork();
    if (pid == -1)
    {
        //Failure of Fork
        perror("fork fails");
        exit(EXIT_FAILURE);
    }
    if (pid == 0)
    {
        int out = 0;
        char data[26];
        memset(data, '\0', sizeof(data));
        msg = (char *)shmat(shmid, NULL, 0);
        while (1)
        {
            //lock the entry
            sem_wait(full);
            data[out] = msg[out];
            out = (out + 1) % 10;
            if (out == 0)
            {
                printf("\tc:%s\n", data);
                sleep(1);
            }
            //unlock the entry
            sem_post(empty);
        }
        shmdt(msg);
    }
    else
    {
        int in = 0;
        char ch = 'A';
        msg = (char *)shmat(shmid, NULL, 0);
        while (1)
        {
            //lock the entry
            sem_wait(empty);
            msg[in] = ch;
            in = (in + 1) % 10;
            ch++;
            if (in == 0)
            {
                ch = 'A';
                printf("p:%s\n", msg);
                sleep(1);
            }
            //unlock the entry
\            sem_post(full);
        }
        shmdt(msg);
    }
    return 0;
}