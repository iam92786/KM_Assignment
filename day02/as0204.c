//4.	Write an Linux System Programming copy one file content to another file using mmap() system call
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<sys/mman.h>



int main (int argc, char *argv[])
{
    int fd1, fd2, ret, i;
    unsigned char *filedata1 , *filedata2 ; 
    unsigned char *temp1 = NULL, *temp2 = NULL;

    struct stat metadat;

    //open source file
    fd1 = open(argv[1],O_RDONLY);
    if (fd1 < 0)
    {
        perror("fd1 : open() failed ! :");
        _exit(0);
    }
        //open file
    fd2 = open(argv[2],O_RDWR | O_CREAT, 0666);
    if (fd2 < 0)
    {
        perror("fd2 : open() failed ! :");
        _exit(0);
    }

    //find the length of file 1
    ret = fstat(fd1,&metadat);
    if (ret < 0)
    {
        perror("fstat() failed !");
    }
    else
    {
        printf("size of file is %ld\n",metadat.st_size);
    }

    //mmap the file.
    filedata1 = (char*) mmap(0,metadat.st_size,PROT_READ,MAP_PRIVATE,fd2,0);
    filedata2 = (char*) mmap(0,metadat.st_size,PROT_READ | PROT_WRITE,MAP_SHARED,fd2,0);

    temp1 = filedata1;
    temp2 = filedata2;

    for (i = 0; i < metadat.st_size; i++)
    {
        //copy the file content
        *filedata2 = *filedata1;
        filedata1++;
        filedata2++;
    }

    //unmap files or devices into memory
    munmap(temp1,metadat.st_size);
    munmap(temp2,metadat.st_size);

    //closed the above all open files
    close(fd1);
    close(fd2);

    return 0;
}
