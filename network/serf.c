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
#include <stdint.h>
#include <fcntl.h>
#include <sys/time.h>
//#define NUM_THREADS 32
pthread_mutex_t mutex;
long shared_var;
char *bigptr;
char *ptr;
long long int s_chunck;
int64_t l_chunck;
int g_threadnum;
long long int iteration;
float op_time;

int sock;

#define BUFF_SIZE 100000000000
#define ERROR -1

char* port[100];
int IPT= 1313;

long long i;

int server()
{
         int n = 0;
        long long int len = 0, maxlen = s_chunck;
        char buffer[maxlen];
        char *pbuffer = buffer;
        // printf("serverin\n");

        
        for (long long int k = 0; k < iteration; k++)
        {
            n = recv(sock, pbuffer, maxlen, 0);
            
        }
        
    return 0;
}
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


void *workTCP_S(void *args)
{
    long tid, local_var;
    // printf("under tcp\n");
    tid = (long) args;
    pthread_mutex_lock(&mutex);
    local_var = shared_var++;
    server();
    
    pthread_mutex_unlock(&mutex);
    // printf("Thread %ld got %ld\n", tid, local_var);
    pthread_exit(NULL);
    
}
void *workTCP_C(void *args)
{
    long tid, local_var;
    // printf("under tcp\n");
    tid = (long) args;
    
    local_var = shared_var++;

    client();
    // printf("Thread %ld got %ld\n", tid, local_var);
    pthread_exit(NULL);
    
}

int threadwork_Ser(int NUM_THREADS)
{
    printf("server in\n");
    pthread_t threads[NUM_THREADS]; long tid; int rc;
    pthread_mutex_init(&mutex, NULL); shared_var = 0;
    struct timeval  start, end;


    int SERVER_PORT = 8877;


    long long int loop=0;

    struct sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = SOCK_DGRAM;

    server_address.sin_port = htons(SERVER_PORT);

    server_address.sin_addr.s_addr = htonl(INADDR_ANY);

    int listen_sock;
    if ((listen_sock = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
        printf("could not create listen socket\n");
        return 1;
    }

    if ((bind(listen_sock, (struct sockaddr *)&server_address, sizeof(server_address))) < 0) {
        printf("could not bind socket\n");
        return 1;
    }

    int wait_size = 16;  // maximum number of waiting clients, after which
                         // dropping begins
    if (listen(listen_sock, wait_size) < 0) {
        printf("could not open socket for listening\n");
        return 1;
    }

    struct sockaddr_in client_address;
    int client_address_len = 0;

        
        if ((sock = accept(listen_sock, (struct sockaddr *)&client_address, &client_address_len)) < 0) {
            printf("could not open a socket to accept data\n");
            return 1;
        }
        // printf("client connected with ip address: %s\n", inet_ntoa(client_address.sin_addr));
        gettimeofday(&start, NULL);
        
            for (tid = 0; tid < NUM_THREADS; tid++ ) 
                {
                    rc = pthread_create(&threads[tid], NULL, workTCP_S, (void *) tid);
                    if (rc) 
                    {
                        printf("Could not create thread %ld\n", tid);
                    }
                }
              for (tid = 0; tid < NUM_THREADS; tid++ ) 
                {
                    rc = pthread_join(threads[tid], NULL);
                    if (rc) 
                    {
                        printf("Could not join thread %ld\n", tid);
                    }
                }
        
        
        gettimeofday(&end, NULL);



        close(sock);



    close(listen_sock);
    op_time= ((float) (end.tv_usec - start.tv_usec) / 1000000 +(float) (end.tv_sec - start.tv_sec));
    // printf("Time %fs\n", ((float) (end.tv_usec - start.tv_usec) / 1000000 +(float) (end.tv_sec - start.tv_sec)) );
printf("Time in thhread%fs \n",op_time );

}

int threadwork_Cli(int NUM_THREADS)
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
                    rc = pthread_create(&threads[tid], NULL, workTCP_C, (void *) tid);
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
    s_chunck = B_size;
    if (s_chunck == 1)
    {
        l_chunck = 1000000;
    }
    else
    {
        l_chunck = 100000000000;
    }




    iteration = (l_chunck)/(s_chunck*th_num);
    // const char *typo = NULL;
    // typo = ;
    // printf("%s\n",argv[2] );
    int typo = atoi(argv[2]);
    long double LT ,TH;
    
    if (typo == 0)
    {
        // printf("%d\n",typo );
        threadwork_Ser(th_num);
        TH = (l_chunck/1000000)*op_time;
        LT = (op_time*1000)/l_chunck;
        printf("time %fs\n", op_time );

        if (s_chunck == 1)
        {
           printf("TCP\t%d\t%lld\t%Lf mSecs\n",th_num, s_chunck, LT );

        }
        else
        {
            printf("TCP\t%d\t%lld\t%Lf MBps\n",th_num, s_chunck, TH );
        }
        // printf("TCP\t%d\t%lld\t%Lf MBps\n",th_num, s_chunck, TH );
        
    }
    else if (typo == 1){
        threadwork_Cli(th_num);
    
    // printf("TCP\t%d\t%lld\t%Lf mSecs\n",th_num, s_chunck, LT );
    }
    
    return 0;
}