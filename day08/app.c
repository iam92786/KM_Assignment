#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>

int main (void)
{
    int fd;
    fd = open("/dev/mycahr",O_CREAT | O_RDWR);
    if (fd > 0)
    {
        perror("open() failed ! ");
        exit(0);
    }
    

    return 0;
}