/*  Make the necessary includes and set up the variables. 
Unnamed Socket, Two different system */

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include<pthread.h>

void *rx_thread(void *arg);
void *tx_thread(void *arg);


pthread_t a_thread, b_thread;
void *thread_result;
char msg[64], msg_send[64];
int server_sockfd, client_sockfd, res;
int server_len, client_len;
struct sockaddr_in server_address;
struct sockaddr_in client_address;

//Thread handler
void *rx_thread(void *arg)
{
    while(1) {
	    sleep(1);	
        //msg Recived from client
        read(client_sockfd, &msg, sizeof(msg));
        printf("|| Msg from Client ||\n%s\n",msg);

        //msg Send to client
        //fgets(msg_send,sizeof(msg_send),stdin);
        //write(client_sockfd, &msg_send, sizeof(msg_send));
    }
}

void *tx_thread(void *arg)
{
    while(1) {
	    sleep(1);	
        //msg Recived from client
        //read(client_sockfd, &msg, sizeof(msg));
        //printf(">>Msg from Client : %s\n",msg);

        //msg Send to client
        fgets(msg_send,sizeof(msg_send),stdin);
        write(client_sockfd, &msg_send, sizeof(msg_send));
    }
}


int main()
{


/*  Create an unnamed socket for the server.  */

    server_sockfd = socket(AF_INET, SOCK_STREAM, 0);

/*  Name the socket.  */

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_address.sin_port = 9734;
    server_len = sizeof(server_address);
    bind(server_sockfd, (struct sockaddr *)&server_address, server_len);

/*  Create a connection queue and wait for clients.  */

    listen(server_sockfd, 5);

    client_len = sizeof(client_address);
    client_sockfd = accept(server_sockfd, (struct sockaddr *)&client_address, &client_len);
    

    //create thread

    //creat rx thread
    res = pthread_create(&a_thread,NULL,rx_thread, NULL);
    if (res != 0)
    {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }
    
    //creat tx thread
    res = pthread_create(&b_thread,NULL,tx_thread, NULL);
    if (res != 0)
    {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }
    
    //joined here
    res = pthread_join(a_thread, &thread_result);
    if (res != 0)
    {
        perror("Threda join Failed !");
        exit(EXIT_FAILURE);
    }

    //threda join here
    res = pthread_join(b_thread, &thread_result);
    if (res != 0)
    {
        perror("Threda join Failed !");
        exit(EXIT_FAILURE);
    }
    
    close(client_sockfd);
    return 0;

}
