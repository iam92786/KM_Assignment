
//du command

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
    
    //count number of byte
    while (ret)
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

    }   
    if(count <= 4095)
    {
        ret = write(1,"4.0k",4);
        ret = write(1,"\t",1);
        ret = write(1,argv[1], sizeof(argv[1]));
    }
    else if(count > 4096)
    {
        ret = write(1,"4.0k",4);
        ret = write(1,"\t",1);
        ret = write(1,argv[1],sizeof(argv[1]));
    }

    write(1,"\n",1);
    close(fd);
    

    return 0;
}