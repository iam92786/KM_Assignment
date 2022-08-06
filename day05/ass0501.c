/*
Assignment 1:
Write a producer and consumer problem using fork() and shared memory. 
Synchronizing producer and consumer process using POSIX signals*/

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

int main (void)
{
    int status;
    int res;
    shmid = shmget(10,1024,0666 | IPC_CREAT);
    if (shmid == -1)
    {
        perror("shared memeory failed !");
        exit(0);
    }
    

    pid = fork();
    if (pid == 0)
    {//Child Process == Consumer
        //send Signal to Producer
        kill(getppid(), SIGUSR2);
        
        //signal initialization
        (void)signal(SIGUSR1,consumer_signal);

        //wait for signal (recived from Producer)
        while (1)
        {
            pause();
        }
        exit(0);
        
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