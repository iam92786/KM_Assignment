//write own 'cp' command

#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>

#define SIZE 1

//int my_cp (source, destination);

int main (int argc, char *argv[])
{
		int fd1,fd2,ret,src,dest;
		char buff[SIZE];

		//open source file
		fd1 = open(argv[1], O_RDONLY);
		if(fd1 < 0)
		{
				perror("open() for source file failed ! :");
				exit(0);
		}

		//open dest file
		fd2 = open(argv[2],O_WRONLY | O_CREAT);
		if(fd2 < 0)
		{
				perror("open() for destination file failed ! :");
				exit(0);
		}

		//copy data of source file into Destination file
		while(src = read(fd1,&buff, SIZE) > 0)
		{
				if(write(fd2,&buff, src) != src)
				{
						perror("write() failed! :");
				}

				if(src == -1)
				{
						perror("read() failed ! :");
				}
		}

		close(fd1);
		close(fd2);

		return 0;
}


