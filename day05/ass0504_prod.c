/*
Assignment 4: 
Write a separate program for producer.c and consumer.c using Shared Memory, 
named semaphores without using fork() and exec() system calls.
*/
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


int shmid;
char *msg;
sem_t *empty, *full;

//Producer
int main()
{
    shmid = shmget(10, 1024, 0666 | IPC_CREAT);
    if (shmid == -1)
    {
        perror("Shmid() failed !");
        exit(0);
    }

    full = sem_open("conssem", O_CREAT, 0664, 0);
    empty = sem_open("prodsem", O_CREAT, 0664, 26);

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
        sem_post(full);
    }
    //detach the shared memory
    shmdt(msg);
    return 0;
}