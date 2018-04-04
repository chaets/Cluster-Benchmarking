#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include<string.h>
#include <immintrin.h>
#include <stdint.h>
//#include <sys/time.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>

int g_threadnum;
long double thr_put= 0;
long double latency= 0;


# define ITERATIONS  1000000000000;
long long int ITR;
long long int operations=0;
pthread_mutex_t mutex;

long shared_var;

void *workQP(void *args)//Quarter precision 
{
    long tid, local_var;
    char x1;
    char x2;
    char x3;
    char x4;
    char x5;
    char x6;
    char x7;
    char x8;
    // clock_t start ,end;
    // double interval;
    int64_t i;
    // printf("Quarter\n");
    tid = (long) args;
    pthread_mutex_lock(&mutex);
    // start = clock();
    for ( i = 0; i < ITR ; )//10 operation including increament and operation Addidtion
    {
         x1 = 'f' + 'b' ;
         x2 = 'g' + '#';
         x3 = 'n' + '$' ;
         x4 = 'j' +  't';
         x5 = 'w' + 'm';
         x7 = 'q' + 'z';
         x6 = 'b' - 'a';
         x8 = 'p' + 'f';
        operations = operations + 10;
        i=i+10;
    }
    // printf("%ld\n",i);
    operations++;
    local_var = shared_var++;
    pthread_mutex_unlock(&mutex);
    // end = clock();
    // interval = (end - start) / (double) CLOCKS_PER_SEC;
    pthread_exit(NULL);
}

void *workHP(void *args)//Half precision 
{
    long tid, local_var;
    short x1 = 8976 + 7651;
        short x3 ;
        short x2 ;
        short x4 ;
        short x5 ;
        short x6 ;
        short x7 ;
        short x8 ;
    // clock_t start ,end;
    // double interval;
    int64_t i;
    tid = (long) args;
    // printf("Half\n");
    // start = clock();
    pthread_mutex_lock(&mutex);
    for ( i = 0; i < ITR ; )
    {
        x1 = 8976 + 7651;
        x2 = 12348 + 17651;
        x3 = 32000 * 1;
        x4 = (-13671) * 2;
        x5 = 5690 + 8911;
        x6 = 1234 + 7651;
        x7 = 5677 + 12351;
        x8 = 4400 + 9109;
    // 
        operations = operations + 10;
    // pthread_mutex_unlock(&mutex);
        i=i+10;
    }
    // printf("%ld\n",i);
    // pthread_mutex_lock(&mutex);
    local_var = shared_var++;
    pthread_mutex_unlock(&mutex);
    // end = clock();
    // interval = (end - start) / (double) CLOCKS_PER_SEC;
    pthread_exit(NULL);
}
void *workSP(void *args)//Single precision 
{
    long tid, local_var;
    // clock_t start ,end;
    double interval;
    int64_t i;
    // printf("Single\n");
    __m256 F1 = _mm256_set_ps(2.3254 , 4.5454, 6.5454, 8.9657, 10.055, 12.454, 14.545, 16.0147);
    __m256 F2 = _mm256_set_ps(1.0, 3.0, 5.0, 7.0, 9.0, 11.0, 13.0, 15.0);
    __m256 result;

    tid = (long) args;
    pthread_mutex_lock(&mutex);
    // start = clock();
    for ( i = 0; i < ITR ; )
    {
     result = _mm256_sub_ps(F1, F2);
      operations= operations + 10;
      i=i+10;
	}
    // printf("%ld\n",i);
    local_var = shared_var++;
    pthread_mutex_unlock(&mutex);
    // end = clock();
    pthread_exit(NULL);
}
void *workDP(void *args)
{
    long tid, local_var;
    clock_t start ,end;
    double interval;
    int64_t i;
    __m256d F1 = _mm256_set_pd(10.055, 12.454, 14.545, 16.0147);
    __m256d F2 = _mm256_set_pd(2.3254 , 4.5454, 6.5454, 8.9657);
    __m256d result;

    tid = (long) args;
    pthread_mutex_lock(&mutex);
    // start = clock();
    for ( i = 0; i < ITR ; )
    {
        
     result = _mm256_sub_pd(F1, F2);
      operations = operations + 10;
      // printf("%ld\n",i);
      i=i+10;

	}
    

    local_var = shared_var++;
    pthread_mutex_unlock(&mutex);
    // end = clock();
    // interval = (end - start) / (double) CLOCKS_PER_SEC;
    pthread_exit(NULL);
}

void threadwork(char a , int NUM_THREADS )//Thread function which will be called in main function
 {
     pthread_t threads[NUM_THREADS]; long tid; int rc;
    pthread_mutex_init(&mutex, NULL); shared_var = 0;
    struct timeval  start, end;
    gettimeofday(&start, NULL);
    
    switch(a) {

       case 'Q'  :
          for (tid = 0; tid < NUM_THREADS; tid++) 
        {
            rc = pthread_create(&threads[tid], NULL, workQP, (void *) tid);
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


        case 'H'  :
          for (tid = 0; tid < NUM_THREADS; tid++) 
        {
            rc = pthread_create(&threads[tid], NULL, workHP, (void *) tid);
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

        case 'S'  :
          for (tid = 0; tid < NUM_THREADS; tid++) 
        {
            rc = pthread_create(&threads[tid], NULL, workSP, (void *) tid);
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

        case 'D'  :
          for (tid = 0; tid < NUM_THREADS; tid++) 
        {
            rc = pthread_create(&threads[tid], NULL, workDP, (void *) tid);
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
    thr_put= operations/(((float) (end.tv_usec - start.tv_usec) / 1000000 +(float) (end.tv_sec - start.tv_sec))*1000*1000*1000);
    printf("%c\t%lld\t%d\t%Lf GOPS\t%fs Sec\n",a, operations,NUM_THREADS,thr_put, ((float) (end.tv_usec - start.tv_usec) / 1000000 +(float) (end.tv_sec - start.tv_sec)));

    
}


int main(int argc, char* argv[])
{
    int i;
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
          love = type [0];
          
        }
        
        else if (l_no==1)
        {
          thread_num=line;
          th_num= atoi(thread_num);
        }
        l_no++;

    }

    fclose(fp);
    g_threadnum = th_num;
    ITR = 1000000000000 / th_num;
    threadwork(love, th_num);
  
}
