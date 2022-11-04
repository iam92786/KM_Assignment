//Mini Project

#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<pthread.h>
#include<unistd.h>
#include<signal.h>

void *prod_thread(void *arg);
void *cons_thread(void *arg);
void signal_prod(int sig);
void sinal_cons(int sig);


char buffer[5];
pthread_t a_thread, b_thread;

void signal_prod(int sig)
{
    int in = 0;
    char ch = 'A';
    while (in < 5)
    {
        buffer[in] = ch;
        in++;
        ch++;
    
        if(in == 5)
        {
            in = 0;
            ch = 'A';
            printf("Prod : %s\n",buffer);
            pthread_kill(b_thread, SIGUSR2);
        }
    }
}
void signal_cons(int sig)
{
    int out = 0;
    char data[5];

    while (out < 5)   
    {
        //wait until for buffer to be full and counter to be zero
        data[out] = buffer[out];
        out++;
	}
        if (out == 5)
        {
            out = 0;
            printf("\tCons : %s\n",data);
            pthread_kill(a_thread, SIGUSR1);
        }
}

int main ()
{
    int res;
    void *thread_result;

//creat prod thread
    res = pthread_create(&a_thread,NULL,prod_thread, NULL);
    if (res != 0)
    {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }
    
//creat cons thread
    res = pthread_create(&b_thread,NULL,cons_thread, NULL);
    if (res != 0)
    {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }
    
// prod joined here
    res = pthread_join(a_thread, &thread_result);
    if (res != 0)
    {
        perror("Threda join Failed !");
        exit(EXIT_FAILURE);
    }

//cons threda join here
    res = pthread_join(b_thread, &thread_result);
    if (res != 0)
    {
        perror("Threda join Failed !");
        exit(EXIT_FAILURE);
    }
    
    return 0;
}


//Producer Thread ________________________________________________________//
void *prod_thread(void *arg)
{
    (void) signal(SIGUSR1,signal_prod);

    while(1)
    {
        pause();
    }
    pthread_exit("exit");
}

//Consumer Thread ________________________________________________________//
void *cons_thread(void *arg)
{
        //give signal to producer
    pthread_kill(a_thread, SIGUSR1);

    (void) signal(SIGUSR2,signal_cons);
    

    while (1)   
    {
        pause();
    }
    pthread_exit("exit");
}
