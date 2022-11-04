//Write a system programe your own version of Head command(top 10 lines only)

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

int main (int argc,char *argv[])
{
		int fd, ret, ind = 10;
		char buf;

		//open file 
		fd = open(argv[1], O_RDWR);
		if(fd < 0)
		{
				perror("open() failed ! : ");
				exit(0);
		}
		//read each char one by one
		while(ind)
		{
				ret = read(fd,&buf,1);
				if(ret < 0)
				{
						perror("read() failed ! :");
						exit(0);
				}
				if(buf == '\n')
				{
						ind--;
				}
				//print eachh cahr one by one
				write(1,&buf,1);
		}
		
		//close file 
		ret  = close(fd);
		if(ret < 0)
		{
				perror("close() failed ! : ");
				exit(0);
		}

		return 0;
}


