//1. What is a zombie process? What is an orphan process? WAP to create a zombie process?

#include<stdio.h>
#include<stdlib.h>

#include<unistd.h>


int main (int argc, char *argv[])
{
    pid_t pid;

    pid = fork();
    if(pid == -1)
    {
        perror("fork() iis failed !");
    }

    if (pid == 0)
    {
        //child
        printf("I am child Process\n");
        exit(0);

    }
    else{
        //parents
        sleep(10);
        printf("I am Parents process\n");
    }
    return 0;
}


/*
### Zombie Process:
    A process which has finished the execution but still 
    has entry in the process table to its parents process is known as zombie process.
    
    A process who is terminated but its exit status is not recived by its parents 
    process then such porcess is called Zombie process. 

### Orphan Process:
    A process  whose parents process is terminated, then child process is called
    as Orphans Process.   
*/