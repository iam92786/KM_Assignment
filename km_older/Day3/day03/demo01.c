//Process PID and PPID
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>


int main(int argc, char *argv[])
{
    pid_t pid;

    pid = fork();
    if (pid == 0)
    {
        //child process
        printf("child process : get pid %d\n",getpid());
        printf("child process : get ppid %d\n",getppid());

    }
    else
    {
        //parents process
        printf("Praentd process : get pid %d\n",getpid());
        printf("Praentd process : get ppid %d\n",getppid());
    }
    

    return 0;
}