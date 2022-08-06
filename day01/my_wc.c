//write own wc command (print number of newline,word,byte counts for a file)

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>


int main (int argc, char *argv[])
{

		int fd, nline = 1,word = 1, bytes = 1, ret = 1;
		char buf;

		//open file
		fd = open(argv[1],O_RDONLY);
		if(fd  < 0)
		{
				perror("open() failed ! :");
				exit(0);
		}

		//read file
		while(ret)
		{
				ret = read(fd,&buf,1);
				if(ret < 0)
				{
						perror("read() failed ! :");
						exit(0);
				}
		
				bytes++;

				if (buf == '\n')
				{
					++nline;
				}

				if (buf == ' ')
				{
					++word;
				}
				
		}
		
		printf("%d,%d,%d\n",nline,word,bytes);

		close(fd);

		return 0;
}
