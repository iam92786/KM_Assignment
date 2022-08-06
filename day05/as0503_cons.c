/*
Assignment 3:
Write a separate program for producer and consumer problem using fork(), 
exec() and shared memory. Synchronizing producer and consumer process using POSIX signals.

*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include<fcntl.h>
#include <sys/wait.h>


void consumer_signal(int sig);

pid_t pid;
int ret, shmid;
char *msg;

int main()
{
    shmid = shmget(10, 1024, 0);
    if (shmid == -1)
    {
        perror("Shared memory error!");
        exit(0);
    }

    //child process ->> Consumer
    (void)signal(SIGALRM, consumer_signal);

    ret = kill(getppid(),SIGALRM);
    if(ret  == -1)
    {
        //error cheking
        perror("kill() failed !");
        exit(1);
    }

    while (1)
    {
        pause();
    }
    return 0;
}

//Consumer Signal Handler
void consumer_signal(int sig)
{
    char ch = 'A';
    //char *msg;
    char data[5];
    int x = 5, out = 0;
    //Attach shared memeory 
    msg = shmat(shmid, 0,0);
    while (x > 0)
    {
        data[out] = msg[out];
        out = (out + 1) % 5;
        if (out == 0)
        {
            printf("\t\t\tConsumer : %s\n\n\n",data);
            sleep(1);

        }
        x--;
    }
    //detach the shared memory
    shmdt(msg);
    kill(getppid(), SIGUSR2);    
}