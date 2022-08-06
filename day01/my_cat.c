//Write own "cat" command

#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>

int main (int argc, char *argv[])
{
		int fd,s_rd,ret;
		char buf;
		//printf("%s %s\n",argv[1],argv[2]);
		
		//open file 
		fd = open(argv[1],O_RDWR);
		if(fd < 0)
		{
				perror("open() failed !! : ");
				exit(0);
		}
		
		//read file
		while(s_rd)
		{

			s_rd = read(fd,&buf,1);
			if(s_rd < 0)
			{
					perror("read() failed !! : ");
					exit(0);
			}
			printf("%c",buf);
		}

		ret = close(fd);
		if(ret < 0)
		{
				perror("close failed!! : ");
				exit(0);
		}
		return 0;
}
