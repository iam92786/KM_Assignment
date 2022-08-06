/*
2. Write an application program to take one unsigned int a=0xaabbccdd, 
retrieve and print values separately using MAJOR MACRO like "aab“  and MINOR MACRO like "bccdd”?

*/
#include<stdio.h>
#include<stdlib.h>
#define MAJOR(x) ((0xFFF00000 & x) >> 20)
#define MINOR(x) (0x000FFFFF & x)
int main (void)
{
    unsigned int unum = 0xaabbccdd;
    
    printf("Major numbere : ");
    //printf major number and minor number
    printf("%x\n",MAJOR(unum));
    
    printf("Minor numbere : ");
    printf("%x\n",MINOR(unum));


    return 0;
}