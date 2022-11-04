/*
Assignment 1:
Write a producer and consumer problem using fork() and shared memory. 
Synchronizing producer and consumer process using POSIX signals.

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


void pro(int sig);
void con(int sig);

char Buffer[5];

pid_t pid;
int ret, shmid;
void *thread_result;
char *msg;

int main()
{
    shmid = shmget(10, 1024, 0666 | IPC_CREAT);
    if (shmid == -1)
    {
        perror("Shared memory error!");
        exit(0);
    }

    pid = fork();
    if (pid == 0)
    {
        //child process ->> Consumer
        (void)signal(SIGALRM, con);
        msg = shmat(shmid,0,0);
        //fgets(msg,1024,stdin);
        printf("I am Consumer >> Output : %s\n",msg);
        shmdt(msg);

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

        exit(0);
    }
    else
    {
        //parents process   --> Producer
        (void)signal(SIGALRM, pro);
        msg = shmat(shmid,0,0);
        fgets(msg, 1024,stdin);
        shmdt(msg);

        kill(pid,SIGALRM);
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
        wait(NULL);
    }
    return 0;
}


// producer signal handler(parents process)
void pro(int sig)
{
    msg = shmat(shmid,0,0);
    printf("I am Producer >> Input : ");
    fgets(msg,1024,stdin);
    shmdt(msg);

    ret = kill(pid,SIGALRM);

    if(ret  == -1)
    {
        //error cheking
        perror("kill() failed !");
        exit(1);
    }

}

// consumer signal handler
void con(int sig)
{
    //(void)signal(SIGALRM, con);
    msg = shmat(shmid,0,0);
    //fgets(msg,1024,stdin);
    printf("I am Consumer >> Output : %s\n",msg);
    shmdt(msg);

    ret = kill(getppid(),SIGALRM);
    if(ret  == -1)
    {
        //error cheking
        perror("kill() failed !");
        exit(1);
    }

}
