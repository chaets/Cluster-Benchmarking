
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


#include <unistd.h>
#include <string.h>
#include <sys/types.h>

 
#define PORT     8080
#define MAXLINE 1024


//#define NUM_THREADS 32
pthread_mutex_t mutex;
long shared_var;
char *bigptr;
char *ptr;
long long int s_chunck;
long long int l_chunck = 1073741824;
int g_threadnum;
long long int iteration;

#define BUFF_SIZE 64
#define ERROR -1

char* port[100];
int IPT= 1313;

int i=0;


int server();
int client();

int server()
{
	int fd;
	int port_udp= 50037;
    if ( (fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror( "socket failed" );
        return 1;
    }

    struct sockaddr_in serveraddr;
    memset( &serveraddr, 0, sizeof(serveraddr) );
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons( port_udp );
    port_udp = port_udp+10; 
    serveraddr.sin_addr.s_addr = htonl( INADDR_ANY );

    if ( bind(fd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0 ) {
        perror( "bind failed" );
        return 1;
    }

    char buffer[200];
    for ( int i = 0; i < 4; i++ ) {
        int length = recvfrom( fd, buffer, sizeof(buffer) - 1, 0, NULL, 0 );
        if ( length < 0 ) {
            perror( "recvfrom failed" );
            break;
        }
        buffer[length] = '\0';
        printf( "%d bytes: '%s'\n", length, buffer );
    }

    close( fd );
}

int client()
{
	int fd;
	int port_udp= 50037;
    if ( (fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket failed");
        return 1;
    }

    struct sockaddr_in serveraddr;
    memset( &serveraddr, 0, sizeof(serveraddr) );
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons( port_udp ); 
    port_udp++;             
    serveraddr.sin_addr.s_addr = htonl( 0x7f000001 );  

    for ( int i = 0; i < 4; i++ ) {
        if (sendto( fd, "hello", 5, 0, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0 ) {
            perror( "sendto failed" );
            break;
        }
        printf( "message sent\n" );
    }

    close( fd );
}








void *UDPS(void *args)
{
    long tid, local_var;
    printf("under tcp\n");
    tid = (long) args;
    // pthread_mutex_lock(&mutex);
    local_var = shared_var++;

    // printf("%c\n", memoryalloc(2));
    server();
    // pthread_mutex_unlock(&mutex);
    printf("Thread %ld got %ld\n", tid, local_var);
    pthread_exit(NULL);
    
}
void *UDPC(void *args)
{
    long tid, local_var;
    printf("under tcp\n");
    tid = (long) args;
    // pthread_mutex_lock(&mutex);
    local_var = shared_var++;

    // printf("%c\n", memoryalloc(2));
    client();
    // pthread_mutex_unlock(&mutex);
    printf("Thread %ld got %ld\n", tid, local_var);
    pthread_exit(NULL);
    
}



void threadwork(int NUM_THREADS, const char TY)
{
    pthread_t threads[NUM_THREADS]; long tid; int rc;
    pthread_mutex_init(&mutex, NULL); 
    shared_var = 0;
   	if (TY=='S')
   	{
   		for (tid = 0; tid < NUM_THREADS; tid++) 
                {
                    // printf("threadscreated\n");
                    rc = pthread_create(&threads[tid], NULL, UDPS, (void *) tid);
                    // printf("threadscreated after call %d\n", rc);
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
   	else if(TY=='C')
   	{
   		for (tid = 0; tid < NUM_THREADS; tid++) 
                {
                    // printf("threadscreated\n");
                    rc = pthread_create(&threads[tid], NULL, UDPC, (void *) tid);
                    // printf("threadscreated after call %d\n", rc);
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
          // printf(" line num 0 %c\n", type[2]);
          love = type [2];
          
        }
        else if (l_no==1)
          {
             size=line;
            // printf(" line num 1 %s\n", size);
            B_size= atoi(size);
            // printf(" Block size %lld\n", B_size);
          }
        else if (l_no==2)
        {
          thread_num=line;
          // printf(" line number 2 %s\n", thread_num);
          th_num= atoi(thread_num);
          // printf(" Thread number %d\n", th_num);
        }
        l_no++;

    }

    fclose(fp);
   

    // if (line)
    //     free(line);
    // exit(EXIT_SUCCESS);
    g_threadnum = th_num;
    s_chunck = B_size;
    iteration = l_chunck/(s_chunck*th_num);
    // printf(" I love you %d\n", th_num);
    // printf(" I love you charc%c\n", love);
    const char *typo = NULL;
    typo = argv[2];
    threadwork( th_num, *typo);
    //printf(" I love you osam %d\n", th_num);
    // threadwork(4);
    return 0;
}