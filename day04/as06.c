//6. WAP create two threads using pthreads and print even no and odd no alternatively.

#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<pthread.h>
#include<unistd.h>

void *odd_thread(void *arg);
void *even_thread(void *arg);

int main (void)
{
    int res;
    pthread_t a_thread, b_thread;
    void *thread_result;

//creat odd thread
    res = pthread_create(&a_thread,NULL,odd_thread, NULL);
    if (res != 0)
    {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }
    
//creat even thread
    res = pthread_create(&b_thread,NULL,even_thread, NULL);
    if (res != 0)
    {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }
    
// odd joined here
    res = pthread_join(a_thread, &thread_result);
    if (res != 0)
    {
        perror("Threda join Failed !");
        exit(EXIT_FAILURE);
    }

//even threda join here
    res = pthread_join(b_thread, &thread_result);
    if (res != 0)
    {
        perror("Threda join Failed !");
        exit(EXIT_FAILURE);
    }
    

    return 0;
}

void *odd_thread(void *arg)
{
    int i = 0;
    while (i < 20)
    {
        sleep(1);
        i += 2;
        printf("%d\n",i);

    }
    pthread_exit("exit");
}

void *even_thread(void *arg)
{
    int i = 1;
    while (i < 20)
    {
        i += 2;
        printf("\t%d\n",i);
        sleep(1);

    }
    pthread_exit("exit");
}
