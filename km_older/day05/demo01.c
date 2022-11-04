#include<stdio.h>
#include<stdlib.h>


int main(void)
{

    unsigned int unum = 0x11223344;

    printf("%x = ",unum);  

    printf("%x ",(0xff000000 & unum) >> 24);
    printf("%x ",(0x00ff0000 & unum) >> 16); 
    printf("%x ",(0x0000ff00 & unum) >> 8);
    printf("%x \n",(0x000000ff & unum) >> 0);




    return 0;
}