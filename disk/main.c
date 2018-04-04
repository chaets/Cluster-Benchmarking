#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>
//#define NUM_THREADS 32
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


unsigned int rand_interval(unsigned int max)
{
    unsigned long
    // max <= RAND_MAX < ULONG_MAX, so this is okay.
    num_bins = (unsigned long) max + 1,
    num_rand = (unsigned long) RAND_MAX + 1,
    bin_size = num_rand / num_bins,
    defect   = num_rand % num_bins;

  long x;
  do {
   x = random();
  }
  // This is carefully written not to overflow
  while (num_rand - defect <= (unsigned long)x);

  // Truncated division is intentional
  return x/bin_size;
}



int RSfile()
{
    int sz;
    ptr = (char *) calloc(s_chunck, sizeof(char));
 
    // fd = open("/tmp/foo.txt", O_RDONLY);
 //  if (fd < 0) { perror("r1"); exit(1); }
 

 // for (int i = 0; i < iteration; i++)
 //    {
 //        // sz = read(fd, , 10);
 //    }
  // if ((fd = open("/tmp/foo.txt", O_RDWR|O_APPEND)) >= 0)
  //   {
  //       // char c;
  //       while (read(fd, ptr, s_chunck) == 1)
  //            putchar(*ptr);
  //   }


  // printf("called read(% d, c, 10).  returned that"
  //        " %d bytes  were read.\n", fd, sz);
  // c[sz] = '\0';
  // printf("Those bytes are as follows: % s\n", c);
    // printf("%d %lld\n", fd, position );
    for (int i = 0; i < iteration; i++)
    {

        if (lseek(fd,position,SEEK_SET)<0)
        {
            return 1;
            printf("lseek 0\n");
        }
        read(fd,ptr,s_chunck);
        // printf("%s\n", ptr);
        position= position + (s_chunck/1024);
        count_variable++;
    }
    fsync(fd);
    // close(fd);
    free(ptr);

}

int RRfile()
{   
    
    
    int sz;
    ptr = (char *) calloc(s_chunck, sizeof(char));
 
    // fd = open("/tmp/foo.txt", O_RDONLY);
    // printf("%d %lld\n", fd, position );
    for (int i = 0; i < iteration; i++)
    {
        j = rand_interval(residue);
        if (lseek(fd,j,SEEK_SET)<0)
        {
            return 1;
            printf("lseek not done\n");
        }
        read(fd,ptr,s_chunck);
        // printf("%s\n", ptr);
        // position=+s_chunck;
        count_variable++;
    }
    fsync(fd);
    free(ptr);
    // close(fd);





}

int WRfile()
{
    int sz;
    // bigptr = (char*) calloc(1073741824 ,sizeof (char));
    
    ptr = (char*) calloc(s_chunck ,sizeof (char));
    memset(ptr, 'a', s_chunck*sizeof(char));
    // long long int j = 0;

    // fd = open("/tmp/foo.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
    // printf("FD and position%d %lld\n", fd, position );
    if (fd < 0)
    {
     perror("r1");
     exit(1);
    }
    // printf("iteration  %lld\n", iteration);
    int ls;

    for (int i = 0; i < iteration; i++)
    {
        // j = rand_interval(1024*1024*1024*10);
        j = rand()%SIZE;
        lseek(fd,j,SEEK_SET);
        // printf("lseek   %lld\n", j);

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
    
    

    // printf("called write(% d, \"hello geeks\\n\", %d)."    " It returned %d\n", fd, strlen("hello geeks\n"), sz);

    // close(fd);

}

void WSfile()
{

    int sz;
    // bigptr = (char*) calloc(1073741824 ,sizeof (char));
    ptr = (char*) calloc(s_chunck ,sizeof (char));
    memset(ptr, 'a', s_chunck*sizeof(char));

    fd = open("/tmp/foo.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
    // printf("FD and postion%d %lld\n", fd, position );

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
    

    // printf("called write(% d, \"hello geeks\\n\", %d)."    " It returned %d\n", fd, strlen("hello geeks\n"), sz);

    // close(fd);



}



void *workRS(void *args)
{
    long tid, local_var;
    tid = (long) args;
    pthread_mutex_lock(&mutex);
    local_var = shared_var++;
    // printf("%c\n", memoryalloc(2));
    RSfile();
    pthread_mutex_unlock(&mutex);
    // printf("Thread %ld got %ld\n", tid, local_var);
    pthread_exit(NULL);
}

void *workWS(void *args)
{
    long tid, local_var;
    tid = (long) args;
    pthread_mutex_lock(&mutex);
    local_var = shared_var++;
    // printf("%c\n", memoryalloc(2));
    // printf("about to write FILE\n");
    WSfile();
    pthread_mutex_unlock(&mutex);
    // printf("Thread %ld got %ld\n", tid, local_var);
    pthread_exit(NULL);
}

void *workRR(void *args)
{
    long tid, local_var;
    tid = (long) args;
    pthread_mutex_lock(&mutex);
    local_var = shared_var++;
    // printf("%c\n", memoryalloc(2));
    RRfile();
    pthread_mutex_unlock(&mutex);
    // printf("Thread %ld got %ld\n", tid, local_var);
    pthread_exit(NULL);
}

void *workWR(void *args)
{
    long tid, local_var;
    tid = (long) args;
    pthread_mutex_lock(&mutex);
    local_var = shared_var++;
    // printf("%c\n", memoryalloc(2));
    WRfile();
    pthread_mutex_unlock(&mutex);
    // printf("Thread %ld got %ld\n", tid, local_var);
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
    // printf("elapsed: %fs\n", (float) (end.tv_usec - start.tv_usec) / 1000000 +(float) (end.tv_sec - start.tv_sec));
    thr_put= SIZE/(((float) (end.tv_usec - start.tv_usec) / 1000000 +(float) (end.tv_sec - start.tv_sec))*1024*1024);
    // printf(" Throughput of system is %Lf MB/Sec\n", thr_put );
    printf("%lld\t%d\t%lld\t%Lf\n", SIZE,NUM_THREADS,s_chunck, thr_put);
    if (s_chunck==1024)
    {
        latency = (((float) (end.tv_usec - start.tv_usec) / 1000000 +(float) (end.tv_sec - start.tv_sec))*1000000)/1073741824;
        printf("Latency of system is %Lf Microseconds\n", latency );
        printf("%lld\t%d%lld\t\t\t%Lf\n", SIZE,NUM_THREADS,s_chunck,latency);
    }




    fsync(fd);
    close(fd);
}

int main(int argc, char const *argv[])
{
    /* code */
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
    

    




    fp = fopen(argv[1], "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {

      if (l_no==0)
        {
          
          type=line;
          // printf(" line num 0 %c\n", type[0]);
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


          // love = type [2];
          
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
    // printf("type values %c %c\n", type[0] , type[1] );

    // if (type[0]=='W')
    // {
    //         if (type[1]=='S')
    //     {
    //         task1 = 0;
    //     }
    //     else if (type[1]=='R')
    //     {
    //         task1 = 1;
    //     }
            
    // }
    // else if (type[0]=='R')
    // {
    //         if (type[1]=='S')
    //     {
    //         task1 = 2;
    //     }
    //     else if (type[1]=='R')
    //     {
    //         task1 = 3;
    //     }
            
    // }
    // // open("foo.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    // printf("task1 %d\n", task1);
    // // if (line)
    // //     free(line);
    // // exit(EXIT_SUCCESS);
    g_threadnum = th_num;
    s_chunck = 1024*B_size;
    long long int residue;
    residue= (SIZE)/s_chunck;
    // printf("Residue %lld\n", residue);
    // printf("Size of the Block%ld\n", SIZE);

    iteration= (residue)/th_num;

    // printf("iteration = %lld\n", iteration);
    // printf(" Thread num %d\n", th_num);
    // // printf(" I love you charc%c\n", love);
    // gettimeofday(&start, NULL);
    threadwork(task1, th_num);
    // printf(" I love you osam %d\n", th_num);
    // gettimeofday(&end, NULL);
    // printf("elapsed: %fs\n", (float) (end.tv_usec - start.tv_usec) / 1000000 +(float) (end.tv_sec - start.tv_sec));

    // printf("count variable: %lld\n", count_variable);






    return 0;






}