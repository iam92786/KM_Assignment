/*
4. Write a system programming your own version of head & tail command?

>>>Tail command<<<
*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

int main (int argc , char *argv[])
{
    int fd, ret, count = 0, temp;
    char buf;

    //open file
    fd = open(argv[1],O_RDONLY);
    if(fd < 0)
	{
		perror("read() failed ! :");
    	exit(0);
	}

    //read file and give total newline
    
    while (ret != 0)
    {
        ret = read(fd,&buf,1);
        if(fd < 0)
    	{
	    	perror("read() failed ! :");
    	    exit(0);
	    }
        if (buf == '\n')
        {
            ++count;
        }
        printf("fd = %d\n",fd);
    }    
    close(fd);

    //open file
    fd = open(argv[1],O_RDONLY);
    if(fd < 0)
	{
		perror("read() failed ! :");
    	exit(0);
	}


    //display last 10 line
    while (count - 11)
    {
        ret = read(fd,&buf,1);
        if(fd < 0)
        {
	    	perror("read() failed ! :");
            exit(0);
        }

    }

    while (count)
    {
        ret = read(fd,&buf,1);
        if(fd < 0)
    	{
	    	perror("read() failed ! :");
    	    exit(0);
	    }
        printf("%c",buf);
        count--;
    }    



    printf("count : %d, fd : %d\n",count, fd);
    close(fd);

    return 0;
}
