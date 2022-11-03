using namespace std;
#include<iostream>

int main (void)
{
    int var;
    wchar_t ch=L'A'; // ch is a variable name 
     // of datatype wchar_t 
     // holding value as A
     //since its long character so we should preceed it with L
    cout <<  "Hello WOrld of C++";
    cin >> var;
    cout <<
    printf("%d %d",ch,sizeof(ch));
    printf("\n size of datatype = %d\n",sizeof(wchar_t));
    return 0;
}