/* Producer consumer program using pthreads, Semaphores */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include<signal.h>

int counter;
//buffer
char buffer[26];

void *producer(void *arg);
void *consumer(void *arg);
pthread_t a_thread,b_thread;

void signal_prod(int sig)
{
    counter--;

}

void signal_cons(int sig)
{
    //consumer signal
    counter++;
}



int main() 
{
    int res;
    //pthread_t a_thread,b_thread;
    void *thread_result;
    int print_count1 = 0;

    //Producer thread
    res = pthread_create(&a_thread, NULL, producer, NULL);
    if (res != 0) {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }

    //Consumer thread
    res = pthread_create(&b_thread, NULL, consumer, NULL);
    if (res != 0) {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }

    //wait for Producer thread  
    printf("Wait for pthread_join\n");
    res = pthread_join(a_thread, &thread_result);
    if (res != 0) {
        perror("Thread join failed");
        exit(EXIT_FAILURE);
    }

    //Wait for consumer thread
    res = pthread_join(b_thread, &thread_result);
    if (res != 0) {
        perror("Thread join failed");
        exit(EXIT_FAILURE);
    }
    printf("Thread joined\n");
    exit(EXIT_SUCCESS);
}


//Producer Thread ________________________________________________________//
void *producer(void *arg)
{
    (void) signal(SIGUSR1,signal_cons);
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
        //counter++;
        pthread_kill(b_thread, SIGUSR2);

        sleep(1);

    }
    pthread_exit("exit");
}

//Consumer Thread ________________________________________________________//
void *consumer(void *arg)
{
    (void) signal(SIGUSR1,signal_cons);

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
        pthread_kill(a_thread, SIGUSR1);

        //counter--;
        sleep(1);
    }
    pthread_exit("exit");
}