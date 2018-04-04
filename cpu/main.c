#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include<string.h>
#include <immintrin.h>
//#include <sys/time.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>

int g_threadnum;
long double thr_put= 0;
long double latency= 0;


# define ITERATIONS = 1000000000000;
long long int operations=0;

//#include <unistd.h>

void read_file1(char raj[])
{
    FILE *fp;
   int c;
  
   fp = fopen(raj,"r");
   while(1) {
      c = fgetc(fp);
      if( feof(fp) ) { 
         //break ;
      }
      printf("%c", c);
   }
   fclose(fp);
   /*
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen("D:\Codelite\Test\Cloud_Assignment_1\read1.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1) {
        printf("Retrieved line of length %zu :\n", read);
        printf("%s", line);
    }

    fclose(fp);
    if (line)
        free(line);
    exit(EXIT_SUCCESS);*/
}

//#define NUM_THREADS 32

pthread_mutex_t mutex;

long shared_var;

void *workQP(void *args)
{
    long tid, local_var;
    clock_t start ,end;
    double interval;
    int i;
    tid = (long) args;
    pthread_mutex_lock(&mutex);
    start = clock();
    //printf("%lld\n ITERATIONS", ITERATIONS);
    for ( i = 0; i < ITERATIONS/8 ; i++)
    {
        char x1 = 'f' + 'b' ;
        char x2 = 'g' + '#';
        char x3 = 'n' + '$' ;
        char x4 = 'j' +  't';
        char x5 = 'w' + 'm';
        char x6 = 'b' - 'a';
        char x7 = 'q' + 'z';
        char x8 = 'p' + 'f';
        operations = operations + 10;
        
    }
    operations++;
    local_var = shared_var++;
    pthread_mutex_unlock(&mutex);
    // printf("ThreadHP %ld got %ld\n", tid, local_var);
    end = clock();
    interval = (end - start) / (double) CLOCKS_PER_SEC;
    // printf("Duration for Quarter Precision is : %lf\n ",interval);
    pthread_exit(NULL);
}

void *workHP(void *args)
{
    long tid, local_var;
    clock_t start ,end;
    double interval;
    int i;
    tid = (long) args;
    pthread_mutex_lock(&mutex);
    start = clock();
    //printf("%lld\n ITERATIONS", ITERATIONS);
    for ( i = 0; i < ITERATIONS/10 ; i++)
    {
        short x1 = 8976 + 7651;
        short x2 = 12348 + 17651;
        short x3 = 32000 * 1;
        short x4 = (-13671) * 2;
        short x5 = 5690 + 8911;
        short x6 = 1234 + 7651;
        short x7 = 5677 + 12351;
        short x8 = 4400 + 9109;
        short x9 = x7 + x8;
        short x10 = x4 + 32000;
        operations = operations + 12;
    }
    
    local_var = shared_var++;
    pthread_mutex_unlock(&mutex);
    // printf("ThreadHP %ld got %ld\n", tid, local_var);
    end = clock();
    interval = (end - start) / (double) CLOCKS_PER_SEC;
    // printf("Duration for Half Precision is : %lf\n ",interval);
    pthread_exit(NULL);
}

void *workSP(void *args)
{
    long tid, local_var;
    clock_t start ,end;
    double interval;
    int i;
    __m256 F1 = _mm256_set_ps(2.3254 , 4.5454, 6.5454, 8.9657, 10.055, 12.454, 14.545, 16.0147);
    __m256 F2 = _mm256_set_ps(1.0, 3.0, 5.0, 7.0, 9.0, 11.0, 13.0, 15.0);

    tid = (long) args;
    pthread_mutex_lock(&mutex);
    start = clock();
    for ( i = 0; i < ITERATIONS/8 ; i++)
    {
        /* Initialize the two argument vectors */

      /* Compute the difference between the two vectors */
      __m256 result = _mm256_sub_ps(F1, F2);
      operations= operations + 10;

      /* Display the elements of the result vector */
      //float* f = (float*)&result;
      //printf("%f %f %f %f %f %f %f %f\n", f[0], f[1], f[2], f[3], f[4], f[5], f[6], f[7]);
    }
    local_var = shared_var++;
    pthread_mutex_unlock(&mutex);
    end = clock();
    // interval = (end - start) / (double) CLOCKS_PER_SEC;
    // printf("ThreadSP %ld got %ld\n", tid, local_var);
    // printf("Duration for Single Precision is : %lf\n ",interval);
    pthread_exit(NULL);
}

void *workDP(void *args)
{
    long tid, local_var;
    clock_t start ,end;
    double interval;
    int i;
    __m256d F1 = _mm256_set_pd(10.055, 12.454, 14.545, 16.0147);
    __m256d F2 = _mm256_set_pd(2.3254 , 4.5454, 6.5454, 8.9657);

    tid = (long) args;
    pthread_mutex_lock(&mutex);
    start = clock();
    for ( i = 0; i < ITERATIONS/4 ; i++)
    {
        /* Initialize the two argument vectors */

      /* Compute the difference between the two vectors */
      __m256d result = _mm256_sub_pd(F1, F2);
      operations = operations + 6;

      /* Display the elements of the result vector */
      //float* f = (float*)&result;
      //printf("%f %f %f %f %f %f %f %f\n", f[0], f[1], f[2], f[3], f[4], f[5], f[6], f[7]);
    }
    local_var = shared_var++;
    pthread_mutex_unlock(&mutex);
    end = clock();
    interval = (end - start) / (double) CLOCKS_PER_SEC;
    // printf("ThreadDP %ld got %ld\n", tid, local_var);
    // printf("Duration for Double Precision is : %lf\n ",interval);
    pthread_exit(NULL);
}

void threadwork(char a , int NUM_THREADS )
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
    // printf("elapsed: %fs\n", (float) (end.tv_usec - start.tv_usec) / 1000000 +(float) (end.tv_sec - start.tv_sec));
    thr_put= operations/(((float) (end.tv_usec - start.tv_usec) / 1000000 +(float) (end.tv_sec - start.tv_sec))*1024*1024*1024);
    // printf("Total Operations is %lld\n", operations);
    // printf("Throughput of system is %Lf GB/Sec\n", thr_put );
    printf("%lld\t%d\t%Lf\n", operations,NUM_THREADS,thr_put);

    if (s_chunck==1)
    {
        latency = (((float) (end.tv_usec - start.tv_usec) / 1000000 +(float) (end.tv_sec - start.tv_sec))*1000000)/1073741824;
        printf("Latency of system is %Lf Microseconds\n", latency );
        printf("%lld\t%d\t\t%Lf\n", operations,NUM_THREADS,latency);
    }




 /*
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
    pthread_mutex_destroy(&mutex);
    pthread_exit(NULL);*/
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
          // printf(" line num 0 %c\n", type[2]);
          love = type [0];
          
        }
        
        else if (l_no==1)
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
    // s_chunck = B_size;
    ITERATIONS = ITERATIONS/g_threadnum;
    // printf(" I love you %d\n", th_num);
    // printf(" I love you charc%c\n", love);
    threadwork(love, th_num);
    // printf(" I love you osam %d\n", th_num);
    




































  //   printf("%s\n", argv[1] );
  //   if (!strcmp(argv[1], "cpu_QP_1thread.dat"))
  //      {

  //          printf("i love you11\n");
  //          threadwork(1,1);
  //      }
  //   else if (!strcmp(argv[1], "cpu_QP_2thread.dat")) {
      
  //     ITERATIONS= ITERATIONS/2;
  //     threadwork(2,1);
  //     printf("i love you12\n");
  //     //break; /* optional */ 
  //       }

  //  else if (!strcmp(argv[1], "cpu_QP_4thread.dat")) {
  //     ITERATIONS= ITERATIONS/4;
  //     threadwork(4,1);
  //     printf("i love you14\n");
  //     //break; /* optional */ 
  //       }

  //  else if (!strcmp(argv[1], "cpu_HP_1thread.dat")) {
  //     threadwork(1,2);
  //     printf("i love you21\n");
  //     //break; /* optional */ 
  //       }

  //  else if (!strcmp(argv[1], "cpu_HP_2thread.dat")) {
  //     ITERATIONS= ITERATIONS/2;
  //     threadwork(2,2);
  //     printf("i love you22\n");
  //     //break; /* optional */
  //     }

  //  else if (!strcmp(argv[1], "cpu_HP_4thread.dat")) {
  //     ITERATIONS= ITERATIONS/4;
  //     threadwork(4,2);
  //     printf("i love you24\n");
  //     //break; /* optional */
  //      }

  //  else if (!strcmp(argv[1], "cpu_SP_1thread.dat")) {
  //     threadwork(1,3);
  //     printf("i love you31\n");
  //     //break; /* optional */
  //      }

  //  else if (!strcmp(argv[1], "cpu_SP_2thread.dat")) {
  //     ITERATIONS= ITERATIONS/2;
  //     threadwork(2,3);
  //     printf("i love you32\n");
  //     //break; /* optional */
  //      }

  //  else if (!strcmp(argv[1], "cpu_SP_4thread.dat")) {
  //     ITERATIONS= ITERATIONS/4;
  //     threadwork(4,3);
  //     printf("i love you34\n");
  //     //break; /* optional */
  //      }

  //  else if (!strcmp(argv[1], "cpu_DP_1thread.dat")) {
  //     threadwork(1,4);
  //     printf("i love you41\n");
  //     //break; /* optional */ 
  // }

  //  else if (!strcmp(argv[1], "cpu_DP_2thread.dat")) {
  //     threadwork(2,4);
  //     printf("i love you42\n");
  //     //break; /* optional */
  //      }

  //  else if (!strcmp(argv[1], "cpu_DP_4thread.dat"))
  //   {
  //     threadwork(4,4);
  //     printf("i love you44\n");
  //     //break; /* optional */
  //      }

/*
    FILE *fp;
   int c;
  
   fp = fopen(argv[1],"r");
   while(1) {
      c = fgetc(fp);
      if( feof(fp) ) { 
         //break ;
      }
      printf("%c", c);
   }
   fclose(fp);

*/


    
   
}








/*
#define ITERATIONS 100000

// thread function to calculate Flops
void *threadFunctionFlop(void *arg)
{
	int i;
	double a=5;
	// convert string argument to long
	long iterations=strtol((char*)arg,NULL,0);
	for(i = 0; i < iterations; i++)
	{
		a=a+a;
	}
	return NULL;
}

void flops(int numberOfThreads)
{
	clock_t start, end;
	double cpu_time_used;
	int i;
	double Flops;
	double gFlops;
	long double a=5;
	pthread_t th[10];// array of threads

	long iterations=ITERATIONS/numberOfThreads;
	char iterationStr[20];
	printf(iterationStr, 20, "%lu",iterations);

	printf("\nProgram to find FLOPS for %d threads",numberOfThreads);
	start = clock();
	for(i=0;i<numberOfThreads;i++)
	{
		pthread_create(&th[i],NULL,threadFunctionFlop,iterationStr);
		pthread_join(th[i], NULL);
	}
	pthread_exit(NULL);
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

	printf("\nTime: %f s\n",cpu_time_used);

	Flops=(ITERATIONS)/(double)(cpu_time_used);

	
	
	//Flops=(ITERATIONS)/(cpu_time_used);

	
	gFlops=(double)Flops/1000000000;// Calculate Giga Flops Formula: F lops * 10raised to (-9).

	printf("GFLOPS : %f\n",gFlops);
}

int main()
{

	read_file();
    //int numberOfThreads=4;
	//flops(numberOfThreads);
	return 0;
}
*/