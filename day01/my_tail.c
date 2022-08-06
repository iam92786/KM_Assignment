#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    int count = 0, fd, ret, pos, ch;
    int setting_line_count = 0;
    char buff;

	//OPEN FILE
    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
    {
        perror("OPEN FAILED: ");
    }
    
    //READ FROM THE FIRE
    ret = read(fd, &buff, 1);
    if (ret == -1)
    {
        perror("READ FAILED: ");
    }
    
	//COUNT TOTAL NO OF LINE
    while (ret != 0)
    {
        if (buff == '\n')
        {
            count++;
        }
        ret = read(fd, &buff, 1);
    }
    setting_line_count = count - 9;
    
	//SET CURSOR POSITION
    pos = lseek(fd, 0, SEEK_SET);

    
    count = 0;

    while (count != setting_line_count)
    {
        ret = read(fd, &buff, 1);
        if (buff == '\n')
        {
            count++;
        }
    }

    while (ch = read(fd, &buff, 1))
    {
        write(1, &buff, ch);
    }

    return 0;
}
