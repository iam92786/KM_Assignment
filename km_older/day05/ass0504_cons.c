/*Assignment 4: 
Write a separate program for producer.c and consumer.c using
Shared Memory, named semaphores without using fork() and exec() system calls.*/


#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>

sem_t *empty, *full;
int shmid;
char *msg;

//consumer
int main()
{
    shmid = shmget(10, 1024, 0666);
    if (shmid == -1)
    {
        perror("Shared memory error!");
        exit(0);
    }

    full = sem_open("csem", O_CREAT, 0664, 0);
    empty = sem_open("psem", O_CREAT, 0664, 26);

    int out = 0;
    char data[26];
    memset(data, '\0', sizeof(data));
    msg = (char *)shmat(shmid, NULL, 0);
    while (1)
    {
        sem_wait(full);
        data[out] = msg[out];
        out = (out + 1) % 10;
        if (out == 0)
        {
            printf("\tc:%s\n", data);
            sleep(1);
        }
        sem_post(empty);
    }
    shmdt(msg);
    return 0;
}