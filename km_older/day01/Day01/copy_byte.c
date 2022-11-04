#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int main()
{
    char byte; 
    int in, out; 
    int nread;

    in = open("file.in", O_RDONLY); 
    out = open("file.out", O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR);
    while((nread = read(in,&byte,1)) > 0)
        write(out,&byte,nread);

    exit(0);
}

