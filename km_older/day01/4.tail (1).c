#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    int count = 0, fd, ret, pos, ch;
    int setting_line_count = 0;
    char buff;

    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
    {
        perror("OPEN FAILED: ");
    }
    ret = read(fd, &buff, 1);
    if (ret == -1)
    {
        perror("READ FAILED: ");
    }
    while (ret != 0)
    {
        if (buff == '\n')
        {
            count++;
        }
        ret = read(fd, &buff, 1);
    }
    setting_line_count = count - 9;
    // printf("count:%d,diff_line_count:%d\n", count, setting_line_count);
    pos = lseek(fd, 0, SEEK_SET);
    // printf("position=%d\n", pos);
    count = 0;
    // printf("ret:%d\n", ret);
    while (count != setting_line_count)
    {
        ret = read(fd, &buff, 1);
        if (buff == '\n')
        {
            count++;
        }
    }
    // printf("count:%d\n", count);
    while (ch = read(fd, &buff, 1))
    {
        write(1, &buff, ch);
    }

    return 0;
}
