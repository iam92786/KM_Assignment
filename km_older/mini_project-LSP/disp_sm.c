#include <stdio.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>


struct fb_var_screeninfo var_info;
struct fb_fix_screeninfo fix_info;
char buffer[128];
int img_size, line_length;
#define IMG_HEADER 56
#define IMG_Y_RES 600
#define IMG_X_RES 800

int main(int argc, char *argv[])
{
	int fbfd, fb_size, i,j, fd_img, ret;
	unsigned int *fb_buf;
    unsigned int res;


    if ((fbfd = open("/dev/fb0", O_RDWR)) < 0) 
    {
        exit(1);
    }


    if (ioctl(fbfd, FBIOGET_VSCREENINFO, &var_info)) 
    {
        printf("Bad vscreeninfo ioctl\n");
        exit(2);
    }
    
    if (ioctl(fbfd, FBIOGET_FSCREENINFO, &fix_info)) 
    {
        printf("Bad vscreeninfo ioctl\n");
        exit(2);
    }



    fb_size = var_info.yres * fix_info.line_length;
    printf("line_length %d\nx_res:%d\nx_yres:%d\n",fix_info.line_length,var_info.xres,var_info.yres);
    printf("fb_size %d \n",fb_size);


    //open the BMP image
    fd_img = open("KM_LOGO_800x600_32.bmp",O_RDONLY);
    if(fd_img < 0)
    {
        perror("open () failed for image:");
    }

    //Read image File Header (2 byte only) (BM)
    ret = read(fd_img,buffer,2);
    if (ret < 0)
    {
        perror("read() failed for Image :");
    }


    printf("Magic Number %s\n",buffer);


    if (buffer[0] != 'B' || buffer[1] != 'M')
    {
        printf("Sorry !\nNot a BMP File !\n");
    }



    ret = read(fd_img,&img_size,4);
    if (ret < 0)
    {
        perror("read() failed for Image :");
    }

    //Display img size
    printf("BMP image size is %d\n",img_size);
    

    ret = lseek(fd_img,54,SEEK_SET);
    if (ret < 0)
    {
        perror("lseek() failed for Image :");
    }
    printf("set position of fd_ing %d\n",ret);


    if ((img_size - IMG_HEADER) > fb_size )
    {
        printf("Error : BMP Image Resolution is more than frame buffer resolution\n");
    }
    


    if ((fb_buf = mmap(0, fb_size, PROT_READ|PROT_WRITE, MAP_SHARED, fbfd, 0)) == (void *) -1)
    {
        perror("mmap() failed : ");
        exit(3);
    }
    

    line_length = fix_info.line_length / 4;

    for ( i = IMG_Y_RES - 1; i >= 0; i--)
    {
        for (j = 0; j < IMG_X_RES; j++)
        {
            read(fd_img,&res,4);
            fb_buf[i * line_length + j] = res;
        }
        
    }
    
    munmap(fb_buf, fb_size);
    close(fd_img);
    return 0;
}
