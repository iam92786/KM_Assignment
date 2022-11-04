//touch command

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>


int main (int argc , char *argv[])
{
    int fd, ret, count = 0, temp;
    char buf;

    //craet file if not present, or open with Read mode 
    fd = open(argv[1],O_RDONLY | O_CREAT);
    if(fd < 0)
	{
		perror("read() failed ! :");
    	exit(0);
	}

    //update time metadata of file 

        ret = futimens(fd,)



    close(fd);
    return 0;   
}