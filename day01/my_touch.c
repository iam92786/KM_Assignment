//touch command

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<utime.h>

int main (int argc , char *argv[])
{
    int fd, ret, count = 0;
    char buf;
    struct utimbuf *temp;

    //craet file if not present, or open with Read mode 
    fd = open(argv[1],O_RDONLY | O_CREAT);
    if(fd < 0)
	{
		perror("read() failed ! :");
    	exit(0);
	}

    //update time metadata of file 
    ret = utime(argv[1], temp);

    close(fd);
    return 0;   
}