//6. Write a program your own kill () command?
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<unistd.h>
#include<signal.h>


int main(int argc, char *argv[])
{
    pid_t pid;
    int ret, status;

    pid = fork();
    if (pid == 0)
    {
        //child process
        ret = kill(atoi(argv[1]),atoi(argv[2]));
        if (ret == -1)  
        {
            perror("kill() system call failed !");
        }
        exit(0);

    }
    else
    {
        //parents process
        wait(&status);
    }

    return 0;
}