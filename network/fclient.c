// #include <stdio.h>
// #include <sys/socket.h>
// #include <stdlib.h>
// #include <netinet/in.h>
// #include <string.h>
// #define PORT 8080
  
//   int client();
  

//   int client()
//   {
//     struct sockaddr_in address;
//     int sock = 0, valread;
//     struct sockaddr_in serv_addr;
//     char *hello = "Hello from client";
//     char buffer[17] = {0};
//     if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
//     {
//         printf("\n Socket creation error \n");
//         return -1;
//     }
  
//     memset(&serv_addr, '0', sizeof(serv_addr));
  
//     serv_addr.sin_family = AF_INET;
//     serv_addr.sin_port = htons(PORT);
      
//     // Convert IPv4 and IPv6 addresses from text to binary form
//     if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) 
//     {
//         printf("\nInvalid address/ Address not supported \n");
//         return -1;
//     }
  
//     if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
//     {
//         printf("\nConnection Failed \n");
//         return -1;
//     }
//     int i;
//     for (i = 0; i<50; i++)
//     send(sock , hello , strlen(hello) , 0 );
//     printf("Hello message sent\n");
//     // valread = read( sock , buffer, 1024);
//     // printf("%s\n",buffer );
//   }
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <pthread.h>
#include <fcntl.h>
#define PORT 8080
pthread_mutex_t mutex;
long shared_var;


int server();

int client()
  {
    struct sockaddr_in address;
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    // char *hello = "Hello from client";
    char buffer[17] = {0};
    char *hello ;
    hello = (char*) calloc(1024 ,sizeof (char));
    memset(hello, 'a', 1024*sizeof(char));
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }
  
    memset(&serv_addr, '0', sizeof(serv_addr));
  
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
      
    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) 
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
  
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }
    int i;
    for (i = 0; i<50; i++)
    send(sock , hello , strlen(hello) , 0 );
    printf("Hello message sent\n");
    // valread = read( sock , buffer, 1024);
    // printf("%s\n",buffer );
  }
void *workTCP(void *args)
{
    long tid, local_var;
    tid = (long) args;
    pthread_mutex_lock(&mutex);
    local_var = shared_var++;
    client();
    pthread_mutex_unlock(&mutex);
    printf("Thread %ld got %ld\n", tid, local_var);
    pthread_exit(NULL);
}
void threadwork(int NUM_THREADS)
{
    pthread_t threads[NUM_THREADS]; long tid; int rc;
    pthread_mutex_init(&mutex, NULL); shared_var = 0;
    
              for (tid = 0; tid < NUM_THREADS; tid++) 
            {
                rc = pthread_create(&threads[tid], NULL, workTCP, (void *) tid);
                if (rc) 
                {
                    printf("Could not create thread %ld\n", tid);
                }
            }
            for (tid = 0; tid < NUM_THREADS; tid++) 
            {
                rc = pthread_join(threads[tid], NULL);
                if (rc) 
                {
                    printf("Could not join thread %ld\n", tid);
                }
            }
            
}



int main(int argc, char const *argv[])
{
    threadwork(4);
    return 0;
}