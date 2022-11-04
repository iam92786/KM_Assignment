.//5. Write a program your own version of system() library? 
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<unistd.h>


int main(int argc, char *argv[])
{
    pid_t pid;
    int ret, status, i;
    //char cmd[128];

    pid = fork();
    if (pid == 0)
    {
        //child process
        //ret = execve("/bin/sh",&argv[1],argv);
        ret = execl("/bin/sh", "sh", "-c", argv[1], (char *) NULL);
        if (ret == -1)  
        {
            perror("execve() fails !");
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
