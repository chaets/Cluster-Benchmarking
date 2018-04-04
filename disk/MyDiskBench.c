#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>
pthread_mutex_t mutex;
long shared_var;
char *bigptr;
char *ptr;
long long int s_chunck;
long long int l_chunck;
int g_threadnum;
int fd;
long long int iteration;
long long int index1;
long long int count_variable = 0;
long long int position =0;
long long int residue;
long long int j;
#define SIZE 10000000000
long double latency= 0;


long double thr_put= 0;


int RSfile();
int RRfile();
int WRfile();
void WSfile();

unsigned int rand_interval(unsigned int max);


unsigned int rand_interval(unsigned int max)// Randon number generator function
{
    unsigned long
    num_bins = (unsigned long) max + 1,
    num_rand = (unsigned long) RAND_MAX + 1,
    bin_size = num_rand / num_bins,
    defect   = num_rand % num_bins;

  long x;
  do {
   x = random();
  }
  while (num_rand - defect <= (unsigned long)x);

  return x/bin_size;
}



int RSfile()// read Sequenctial function
{
    int sz;
    ptr = (char *) calloc(s_chunck, sizeof(char));
 
    for (int i = 0; i < iteration; i++)
    {

        if (lseek(fd,position,SEEK_SET)<0)
        {
            return 1;
            printf("lseek 0\n");
        }
        read(fd,ptr,s_chunck);
        position= position + (s_chunck/1024);
        count_variable++;
    }
    fsync(fd);
    free(ptr);

}

int RRfile() //Read Random Function
{   
    
    
    int sz;
    ptr = (char *) calloc(s_chunck, sizeof(char));
 
    for (int i = 0; i < iteration; i++)
    {
        j = rand_interval(residue);
        if (lseek(fd,j,SEEK_SET)<0)
        {
            return 1;
            printf("lseek not done\n");
        }
        read(fd,ptr,s_chunck);
        count_variable++;
    }
    fsync(fd);
    free(ptr);
}

int WRfile()//Write Random Function
{
    int sz;
    
    ptr = (char*) calloc(s_chunck ,sizeof (char));
    memset(ptr, 'a', s_chunck*sizeof(char));
    if (fd < 0)
    {
     perror("r1");
     exit(1);
    }
    int ls;

    for (int i = 0; i < iteration; i++)
    {
        j = rand()%SIZE;
        lseek(fd,j,SEEK_SET);

        if (lseek(fd,j,SEEK_SET)<0)
        {
            printf("return without writing\n");
            return 1;
        }
        sz = write(fd, ptr, s_chunck);
        count_variable++;

    }
    fsync(fd);
    free(ptr);
}

void WSfile() //write Sequential function
{

    int sz;
    ptr = (char*) calloc(s_chunck ,sizeof (char));
    memset(ptr, 'a', s_chunck*sizeof(char));

    fd = open("/tmp/foo.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);

    if (fd < 0)
    {
     perror("r1");
     exit(1);
    }
    for (int i = 0; i < iteration; i++)
    {
        sz = write(fd, ptr, s_chunck);
        count_variable++;
    }
    fsync(fd);
    free(ptr);
    

}



void *workRS(void *args)//thread function will be called inside Threadwork Function
{
    long tid, local_var;
    tid = (long) args;
    pthread_mutex_lock(&mutex);
    local_var = shared_var++;
    RSfile();
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}

void *workWS(void *args)//thread function will be called inside Threadwork Function
{
    long tid, local_var;
    tid = (long) args;
    pthread_mutex_lock(&mutex);
    local_var = shared_var++;
    WSfile();
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}

void *workRR(void *args)//thread function will be called inside Threadwork Function
{
    long tid, local_var;
    tid = (long) args;
    pthread_mutex_lock(&mutex);
    local_var = shared_var++;
    RRfile();
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}

void *workWR(void *args)//thread function will be called inside Threadwork Function
{
    long tid, local_var;
    tid = (long) args;
    pthread_mutex_lock(&mutex);
    local_var = shared_var++;
    WRfile();
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}


void threadwork(int a, int NUM_THREADS)
 {
     pthread_t threads[NUM_THREADS]; long tid; int rc;
    pthread_mutex_init(&mutex, NULL); shared_var = 0;
    if (a==0||a==1)
    {
        fd = open("/tmp/foo.txt", O_WRONLY | O_CREAT | O_APPEND | O_TRUNC , 0644);
    }
    else 
    {
        fd = open("/tmp/foo.txt", O_RDONLY);
    }
    struct timeval  start, end;
    gettimeofday(&start, NULL);

    switch(a) {

       case 0  :
          for (tid = 0; tid < NUM_THREADS; tid++) 
        {
            rc = pthread_create(&threads[tid], NULL, workWS, (void *) tid);
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
          break; /* optional */


        case 1  :
          for (tid = 0; tid < NUM_THREADS; tid++) 
        {
            rc = pthread_create(&threads[tid], NULL, workWR, (void *) tid);
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
          break; /* optional */

        case 2  :
          for (tid = 0; tid < NUM_THREADS; tid++) 
        {
            rc = pthread_create(&threads[tid], NULL, workRS, (void *) tid);
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
          break; /* optional */

        case 3  :
          for (tid = 0; tid < NUM_THREADS; tid++) 
        {
            rc = pthread_create(&threads[tid], NULL, workRR, (void *) tid);
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
        break;
    }
    gettimeofday(&end, NULL);
    
    if (s_chunck==1024)
    {
        latency = (((float) (end.tv_usec - start.tv_usec) / 1000000 +(float) (end.tv_sec - start.tv_sec))*1000000)/1073741824;
        // printf("Latency of system is %Lf Microseconds\n", latency );
        printf("Case %d\t%ld\t%d\t%lld\t%Lf\n",a, SIZE,NUM_THREADS,s_chunck,latency);
    }
    else
    {
   	thr_put= SIZE/(((float) (end.tv_usec - start.tv_usec) / 1000000 +(float) (end.tv_sec - start.tv_sec))*1024*1024);
    printf("Case %d\t%ld\t%d\t%lld\t%Lf\n",a, SIZE,NUM_THREADS,s_chunck, thr_put);
    }




    fsync(fd);
    close(fd);
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
    int task1 =0;
    

    
//process for reading a file



    fp = fopen(argv[1], "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {

      if (l_no==0)
        {
          
          type=line;
          if (type[0]=='W')
            {
                if (type[1]=='S')
                {
                    task1 = 0;
                }
                else if (type[1]=='R')
                {
                    task1 = 1;
                }
            
            }
          else if (type[0]=='R')
            {
                if (type[1]=='S')
                    {
                        task1 = 2;
                    }
                else if (type[1]=='R')
                    {
                        task1 = 3;
                    }

            }
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
    long long int residue;
    residue= (SIZE)/s_chunck;

    iteration= (residue)/th_num;

    threadwork(task1, th_num);

    return 0;
}