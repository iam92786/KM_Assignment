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


void producer_signal(int sig);
void consumer_signal(int sig);

pid_t pid;
int shmid;
char *msg;
int count;


int main()
{
    int ret, status;
    char *filename[] = {"./cons",NULL};
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
        
        //ret = execve("/home/im-rt-lp-1148/km/day05",filename,NULL);
        ret = execl("/home/im-rt-lp-1148/km/day05","cons",NULL);
        if (ret == -1)
        {
            perror("execlp () failed !");
            exit(0);
        }
        
    }
    else
    {//parrents Process == Producer
     
        //signal initialization
        (void)signal(SIGUSR2,producer_signal);

        //wait for signal (recived from Consumer)
        while (1)
        {
            pause();
        }   
        wait(&status);
    }

    return 0;
}

//Producer Signal Handler
void producer_signal(int sig)
{
    char ch = 'A';
    //char *msg;
    int x = 0, in = 0;
    //Attach shared memeory 
    msg = shmat(shmid,0,0);
    while (x < 5)
    {
        msg[in] = ch;
        in = (in + 1) % 5;
        ch++;
        if(in == 0)
            {
                ch = 'A';
                printf(">> Producer = %s\n",msg);
                sleep(1);

            }
        x++;
    }
    //detach the shared memory
    shmdt(msg);
    kill(pid,SIGUSR1);
}