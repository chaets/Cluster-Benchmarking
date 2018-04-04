#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <pthread.h>
#include <fcntl.h>
#define PORT 11155
pthread_mutex_t mutex;
long shared_var;


// int server();

// int server()
// {


//     int server_fd, new_socket, valread;
//     struct sockaddr_in address;
//     int opt = 1;
//     int addrlen = sizeof(address);
//     char buffer[17] = {0};
//     char *hello ;
//     hello = (char*) calloc(1024 ,sizeof (char));
//     memset(hello, 'a', 1024*sizeof(char));
//     // int j = strlen(hello);
//     // char buffer[j] = {0};
      
//     // Creating socket file descriptor
//     if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
//     {
//         perror("socket failed");
//         exit(EXIT_FAILURE);
//     }
      
//     // Forcefully attaching socket to the port 8080
//     if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
//                                                   &opt, sizeof(opt)))
//     {
//         perror("setsockopt");
//         exit(EXIT_FAILURE);
//     }

//     address.sin_family = AF_INET;
//     address.sin_addr.s_addr = INADDR_ANY;

//     address.sin_port = htons( PORT );
//      printf("I love you\n"); 
//     // Forcefully attaching socket to the port 8080
//     if (bind(server_fd, (struct sockaddr *)&address, 
//                                  sizeof(address))<0)
//     {
//         perror("bind failed");
//         exit(EXIT_FAILURE);
//     }
//     printf("AFTER BIND\n");
//     if (listen(server_fd, 3) < 0)
//     {
//         perror("listen");
//         exit(EXIT_FAILURE);
//     }
//     printf("AFTER LISTEN\n");
//     if ((new_socket = accept(server_fd, (struct sockaddr *)&address, 
//                        (socklen_t*)&addrlen))<0)
//     {
//         perror("accept");
//         exit(EXIT_FAILURE);
//     }
//     int i =0;
//     while(i<50)
//     {
//     valread = read( new_socket , buffer, 1024);
//     printf("%s\n",buffer );
//     i++;
//     }
//     // send(new_socket , hello , strlen(hello) , 0 );
//     // printf("Hello message sent\n");
//     // return 0;
// }
void *workTCP(void *args)
{
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[17] = {0};
    char *hello ;
    hello = (char*) calloc(1024 ,sizeof (char));
    memset(hello, 'a', 1024*sizeof(char));
    // int j = strlen(hello);
    // char buffer[j] = {0};
      
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
      
    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                                                  &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;

    address.sin_port = htons( PORT );
     printf("I love you\n"); 
    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address, 
                                 sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    printf("AFTER BIND\n");
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    long tid, local_var;
    tid = (long) args;
    //pthread_mutex_lock(&mutex);
    printf("AFTER LISTEN\n");
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, 
                       (socklen_t*)&addrlen))<0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    int i =0;
    while(i<50)
    {
    valread = read( new_socket , buffer, 1024);
    printf("%s\n",buffer );
    i++;
    }
    
    local_var = shared_var++;
    // server();
    //pthread_mutex_unlock(&mutex);
    printf("Thread %ld got %ld\n", tid, local_var);
    pthread_exit(NULL);
}
void threadwork(int NUM_THREADS)
{
    pthread_t threads[NUM_THREADS]; long tid; int rc;
    pthread_mutex_init(&mutex, NULL); shared_var = 0;
    
              for (tid = 0; tid < NUM_THREADS; tid++) 
            {
                printf("threadscreated\n");
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
    threadwork(1);
    return 0;
}