//2.	Write a program to read framebuffer fixed size information? 
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#include<fcntl.h>
#include<linux/fb.h>
#include<sys/ioctl.h>

int main (int argc, char *argv[])
{
    int fd;
    struct fb_fix_screeninfo info;


    //open file
    fd = open(argv[1], O_RDONLY);
    if (fd < 0)
    {
        perror("open() failed ! :");
        exit(0);
    }
    
    ioctl(fd,FBIOGET_FSCREENINFO, &info);
    printf("Char id = %s\nLen of Frame Buffer mem = %d\nType %d\n",
    info.id,info.smem_len,info.type);

    close(fd);
    return 0;
}