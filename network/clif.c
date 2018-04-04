#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <string.h>
pthread_mutex_t mutex;
long shared_var;
char *bigptr;
char *ptr;
long long int s_chunck;
long long int l_chunck = 1073741824;
int g_threadnum;
long long int iteration;
int SERVER_PORT = 8877;
int sock;

#define BUFF_SIZE 64
#define ERROR -1

char* port[100];
int IPT= 1313;

int i=0;


int client( )
{

    char* data_to_send ;
    data_to_send = (char*) calloc(s_chunck ,sizeof (char));
    memset(data_to_send, 'a', s_chunck*sizeof(char));
    for (long long int k = 0; k < iteration; k++)
    {
        send(sock, data_to_send, s_chunck, 0);
    }
    
    
    
    free(data_to_send);
    
    
    return 0;
}








void *workTCP(void *args)
{
    long tid, local_var;
    printf("under tcp\n");
    tid = (long) args;
    
    local_var = shared_var++;

    client();
    printf("Thread %ld got %ld\n", tid, local_var);
    pthread_exit(NULL);
    
}

int threadwork(int NUM_THREADS)
{
    pthread_t threads[NUM_THREADS]; long tid; int rc;
    pthread_mutex_init(&mutex, NULL); 
    shared_var = 0;
    int SERVER_PORT = 8877;

        const char* server_name = "localhost";

    struct sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = SOCK_DGRAM;

    inet_pton(SOCK_DGRAM, server_name, &server_address.sin_addr);

    server_address.sin_port = htons(SERVER_PORT);

    
    if ((sock = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
        printf("could not create socket\n");
        return 1;
    }

    if (connect(sock, (struct sockaddr*)&server_address,
                sizeof(server_address)) < 0) {
        printf("could not connect to server\n");
        return 1;
    }

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



    close(sock);

}

int main(int argc, char const *argv[])
{
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    int l_no=0;
    char str[3][10];
    char * type = NULL;
    char * thread_num = NULL;
    char * size = NULL;
    long long int  B_size;
    int th_num;
    char love;




    fp = fopen(argv[1], "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {

      if (l_no==0)
        {
          
          type=line;
          love = type [2];
          
        }
        else if (l_no==1)
          {
             size=line;
            B_size= atoi(size);
          }
        else if (l_no==2)
        {
          thread_num=line;
          th_num= atoi(thread_num);
        }
        l_no++;

    }

    fclose(fp);
    g_threadnum = th_num;
    s_chunck = 1024*B_size;
    iteration = 100000000000/(s_chunck*th_num);
    threadwork( th_num);
    return 0;
}