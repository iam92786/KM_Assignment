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
#define IMG_Y_RES 1080
#define IMG_X_RES 1920

int main(int argc, char *argv[])
{
    int fbfd, fb_size, i,j, fd_img, ret;
    unsigned int *fb_buf;
    unsigned int res;

    //Open frame buffer memory
    if ((fbfd = open("/dev/fb0", O_RDWR)) < 0) 
    {
        exit(1);
    }

    //Get variable display parameters
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


    // Size of frame buffer = (X-resolution * Y-resolution * bytes per pixel) */
    //fb_size = var_info.xres*var_info.yres*(var_info.bits_per_pixel/8);
    //Calculate the frame buffer size
    //fb_size = (fix_info.line_length * var_info.yres * (var_info.bits_per_pixel / 8));
    fb_size = var_info.yres * fix_info.line_length;
    printf("line_length %d\nx_res:%d\nx_yres:%d\n",fix_info.line_length,var_info.xres,var_info.yres);
    printf("fb_size %d \n",fb_size);


    //open the BMP image
    fd_img = open("KM-logo_1920_1080_32bpp.bmp",O_RDONLY);
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

    //display Magic number
    printf("Magic Number %s\n",buffer);

    //identify its Magic Number
    if (buffer[0] != 'B' || buffer[1] != 'M')
    {
        printf("Sorry !\nNot a BMP File !\n");
    }

    //read next 4 byte from BMP image
    //which contain infor about image size
    ret = read(fd_img,&img_size,4);
    if (ret < 0)
    {
        perror("read() failed for Image :");
    }

    //Display img size
    printf("BMP image size is %d\n",img_size);
    
    //set img fd to 54 position
    ret = lseek(fd_img,54,SEEK_SET);
    if (ret < 0)
    {
        perror("lseek() failed for Image :");
    }
    printf("set position of fd_ing %d\n",ret);

    //compare BMP image Resolution with Frame Buffere Resolution
    if ((img_size - IMG_HEADER) > fb_size )
    {
        printf("Error : BMP Image Resolution is more than frame buffer resolution\n");
    }
    

    //Framebuffer mapping with mmap() system call in to our process virtual memory space(Process Addresses Space)
    /
    if ((fb_buf = mmap(0, fb_size, PROT_READ|PROT_WRITE, MAP_SHARED, fbfd, 0)) == (void *) -1)
    {
        perror("mmap() failed : ");
        exit(3);
    }
    /*
    	mmap() : mapped disk file open as file discriptor (fd) in to process virtual memory space.
    	HERE (In above case) : 
    		1st arg : addr in process virtual memory space
    		2nd arg : Size of mapped area in virtual memory space
    		
    		5rd arg : frame buffere file discriptor "which is i want to mapped in my current process virtual memeory space"
    		6th arg : offset in frame buffere "from whhich memory location in frame buffere i want to be mapped in my process virtual memory space" 
    		
    	CONCLUSION : here we are mapped frame buffer in to our process virtual memory space and filling the frame buffer with the image data (int = 4 byte), This HOW WE ARE FILLING DATA IN TO FRAME BUFFER ! 
    */
    
    //claculate line length
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
