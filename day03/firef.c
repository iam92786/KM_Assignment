#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<unistd.h>


int main(int argc, char *argv[])
{
    pid_t pid;
    int ret, status;

        ret = system("firefox");
        if (ret == -1)  
        {
            perror("execve() fails !");
            exit(0);
        }


    return 0;
}