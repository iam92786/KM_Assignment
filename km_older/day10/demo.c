#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
int main(int argc,char* argv[])
{
	FILE* fd;
	int count=0,i,j;
	char buf[128],dep[100],dep1[20],command_buff[50];
	char* p1,*p2;
	if(argc!=2)
	{
		printf("sudo <./a.out> <file name>");
		return -1;
	}
	fd = fopen("/lib/modules/5.13.0-52-generic/modules.dep","r");
	if(fd==NULL)
	{
		printf("File not opened\n");
		return 0;
	}

//	fgets(buf,128,fd);
//	printf("%s",buf);
	while(fgets(buf,128,fd))
	{
		if(strstr(buf,argv[1]))
		{
			//for(i=0;buf[i];i++)
			//{
				//if(buf[i]=='/')
			/*	if(p2=strchr(buf,'/'))
				{
					i=p2-buf;
					printf("%d\n",i);
					for(i=i+1 , j=0 ; buf[i]!=':'&buf[i]!='\n' ;j++,i++)
					dep[j]=buf[i];
					dep[j]='\0';
					printf("%s",dep);
				}*/
				if(p2=strchr(buf,':'))
				{
					i=p2-buf;
					printf("%d\n",i);
					for(i=i+1 , j=0 ; buf[i]!=':'&buf[i]!='\n' ;j++,i++)
                                        dep[j]=buf[i];
                                        dep[j]='\0';
                                        printf("%s\n",dep);
					if(p1=strchr(dep,'/'))
					{
						i=p1-dep;
						for(i=i+1,j=0;dep[i]!=':'& buf[i]!='\n';j++,i++)
						dep1[j]=dep[i];
						dep[j]='\0';
						printf("%s",dep1);
					}
					sprintf( command_buff, "sudo insmod %s", dep1 );
					system(command_buff);
					sprintf( command_buff, "sudo insmod %s.ko", argv[1] );
					system(command_buff);
				}
			
		}
	}
}

