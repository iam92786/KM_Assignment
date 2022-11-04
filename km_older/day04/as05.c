//5. WAP producer thread and consumer thread synchronization using pthreads without synchronization mechanisms?

#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<pthread.h>
#include<unistd.h>

void *prod_thread(void *arg);
void *cons_thread(void *arg);
char buffer[5];
int counter = 0;

//Producer Thread ________________________________________________________//
void *prod_thread(void *arg)
{
    int in = 0;
    char ch = 'A';
    while (1)
    {
        while(counter == 5);
    
        //if counter != 5 , then
        buffer[in] = ch;
        in = (in+1)%5;
        ch++;
        if (in == 0)
        {
            ch = 'A';
            printf("Prod : %s\n",buffer);
        }
        counter++;
        sleep(1);

    }
    pthread_exit("exit");
}

//Consumer Thread ________________________________________________________//
void *cons_thread(void *arg)
{
    int out = 0;
    char data[5];

    while (1)   
    {
        //wait until for buffer to be full and counter to be zero
        while (counter == 0);
        data[out] = buffer[out];

        out = (out +1)%5;

        if (out == 0)
        {
            printf("\tCons : %s\n",data);
        }
        counter--;
        sleep(1);
    }
    pthread_exit("exit");
}

int main (void)
{
    int res;
    pthread_t a_thread, b_thread;
    void *thread_result;

//creat odd thread
    res = pthread_create(&a_thread,NULL,prod_thread, NULL);
    if (res != 0)
    {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }
    
//creat even thread
    res = pthread_create(&b_thread,NULL,cons_thread, NULL);
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

