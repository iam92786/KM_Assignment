/*
7. Write a system programming your own version of getchar() 
    standard C Library?

*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>

int main (void)
{
    int ret,i = 0;
    char buf[32];

    //read from the shell terminal
    ret = read(1,buf,32);
    if (ret < 0)
    {
        perror("read() failed ! ");
        exit(0);
    }

    //print input  
    while (buf[i])
    {
        write(1,&buf[i],1);
        i++;

    }

    return 0;
}
