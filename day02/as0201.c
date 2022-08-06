//1.	Write a program show the /dev/input/event0 device name?
#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<linux/input.h>

int main (int argc, char *argv[])
{
    int fd, ret, val;
    char name[256] = "Unknown";

    //open file
    fd = open("/dev/input/event0",O_RDONLY);
    if (fd < 0)
    {
        perror("open() failed ! :");
        _exit(0);
    }

    //read frile information
    ioctl(fd, EVIOCGNAME(sizeof(name)),name);
    printf("/dev/input/events0 : %s\n",name);

    

    return 0;
}