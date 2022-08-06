/*  Make the necessary includes and set up the variables.  */

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include<pthread.h>


int sockfd;
int len,res;
pthread_t a_thread, b_thread;
void *thread_result;
struct sockaddr_in address;
int result;
char msg[64], msg_send[64];

//Thread handler
void *rx_thread(void *arg)
{
    while(1) {
	    sleep(1);	
        //msg Recived from client
        read(sockfd, &msg, sizeof(msg));
        printf("|| Msg from Server ||\n%s\n",msg);

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
        write(sockfd, &msg_send, sizeof(msg_send));
    }
}


int main()
{
/*  Create a socket for the client.  */

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

/*  Name the socket, as agreed with the server.  */

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = 9734;
    len = sizeof(address);

/*  Now connect our socket to the server's socket.  */

    result = connect(sockfd, (struct sockaddr *)&address, len);

    if(result == -1) {
        perror("oops: client2");
        exit(1);
    }

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
    
    close(sockfd);
    return 0;

}