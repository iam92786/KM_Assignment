//3.	Write your own version of cat command using mmap system call?
#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<linux/input.h>
#include<sys/stat.h>
#include<sys/mman.h>

int main (int argc, char *argv[])
{
    int fd, ret, i;
    unsigned char *filedata = NULL, *filedata2 = NULL; 

    struct stat metadat;

    //open file
    fd = open(argv[1],O_RDWR);
    if (fd < 0)
    {
        perror("open() failed ! :");
        _exit(0);
    }

    //metadata
    ret = fstat(fd,&metadat);
    if (ret < 0)
    {
        perror("fstat() failed !");
    }
    else
    {
        printf("size of file is %ld\n",metadat.st_size);
    }
    //mmap the file.
    filedata = (char*) mmap(0,metadat.st_size,PROT_READ,MAP_PRIVATE,fd,0);

    filedata2 = filedata;

    for (i = 0; i < metadat.st_size; i++)
    {
        printf("%c",*filedata);
        filedata++;
    }
    
    //unmmaped the file
    munmap(filedata2,metadat.st_size);

    return 0;
}
