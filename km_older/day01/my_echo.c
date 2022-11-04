//write own version of echo command

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

int main (int argc, char *argv[])
{
	int ret;


	for (int i = 1; i < argc; i++)
	{

		ret = write(1,argv[i], strlen(argv[i]));
		if(ret < 0)
		{
				perror("write () failed !! : ");
				exit(0);
		}
		ret = write(1," ",1);
		if(ret < 0)
		{
				perror("write () failed !! : ");
				exit(0);
		}

	}
	return 0;
}
