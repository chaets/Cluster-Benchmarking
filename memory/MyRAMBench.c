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
long long int s_chunck, ITR;
long long int l_chunck;
int g_threadnum, G=100;
long double thr_put= 0;
long double latency= 0;
float p_time[100], pt=0;
float p_throuput[100],pth=0;
float p_latenency[100],pl=0;
long long int block_RW=0;
#define Rando_var 100000000


void memoryalloc();
void memoryRandalloc();
unsigned int rand_interval(unsigned int max);


unsigned int rand_interval(unsigned int max)//Random number generator
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
void memoryRandalloc()//random memory allocation
{
	long long int i,j;
	for (int i = 0; i < (ITR); )
		{
		  j = rand_interval(Rando_var);
		  i++;
		  memcpy(&bigptr[j], &ptr[j], s_chunck);
		 
		}
}
void memoryalloc()//sequetial memory allocation
{
	long long int i;


	for (int i = 0; i < (ITR); i++)
		{
		  memcpy(&bigptr[block_RW], &ptr[block_RW], s_chunck);
		  block_RW =block_RW +s_chunck;
		}
}
void *workSEQ(void *args)//thread function will be called inside Threadwork Function
{
	long tid, local_var;
	tid = (long) args;
	pthread_mutex_lock(&mutex);
	local_var = shared_var++;
	memoryalloc();
	pthread_mutex_unlock(&mutex);
	// printf("Thread %ld got %ld\n", tid, local_var);
	pthread_exit(NULL);
}
void *workRAND(void *args)//thread function will be called inside Threadwork Function
{
	long tid, local_var;
	tid = (long) args;
	pthread_mutex_lock(&mutex);
	local_var = shared_var++;
	memoryRandalloc();
	pthread_mutex_unlock(&mutex);
	// printf("Thread %ld got %ld\n", tid, local_var);
	pthread_exit(NULL);
}

void threadwork(char type, int NUM_THREADS, long long int a)
{
 	pthread_t threads[NUM_THREADS]; long tid; int rc;
 	pthread_mutex_init(&mutex, NULL); shared_var = 0;
 	struct timeval  start, end;
    
    bigptr = (char*) calloc(1000000000 ,sizeof (char));
	ptr = (char*) calloc(1000000000 ,sizeof (char));
	memset(ptr, 'a', 1000000000*sizeof(char));
	if (ptr == NULL)
				{
				  printf("Could not allocate memory\n");
				  exit(-1);
				}
				else
				  {
				  	// printf("Memory allocated successfully.\n");
				  	if (s_chunck==1)
				  	{
				  		ITR=(100000/(g_threadnum*s_chunck));
				  	}
				  	else
				  	{
				  		ITR=(1000000000/(g_threadnum*s_chunck));
				  		// printf("ITR value%lld\n", ITR );
				  	
				  	}		


				  	
				  	// printf("number of iteration %ld\n", ITR);
				  	
				  	gettimeofday(&start, NULL);
				  	switch(type) 
						    {


						       case 'R' :
						          for (tid = 0; tid < NUM_THREADS; tid++) 
						        {
						            rc = pthread_create(&threads[tid], NULL, workRAND, (void *) tid);
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
						        	
						            rc = pthread_create(&threads[tid], NULL, workSEQ, (void *) tid);
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
							}
					gettimeofday(&end, NULL);
				    // printf("elapsed: %fs\n", ((float) (end.tv_usec - start.tv_usec) / 1000000 +(float) (end.tv_sec - start.tv_sec)));
				    p_time[G]= ((float) (end.tv_usec - start.tv_usec) / 1000000 +(float) (end.tv_sec - start.tv_sec));
				    }
				free(ptr);
	
	free(bigptr);
block_RW=0;	    
}
int main(int argc, char **argv)
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

	//File reader

    // printf(" %s\n", argv[1]);
    fp = fopen(argv[1], "r");

    if (fp == NULL)
        exit(EXIT_FAILURE);
    while ((read = getline(&line, &len, fp)) != -1) 
    {
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
    for(G=0; G<100;G++)
    {
    	threadwork(love, th_num, B_size);
    	pl= pl + p_latenency[G];
    	pth = pth + p_throuput[G];
    	pt=pt + p_time[G];

	}
    long double  LT=0,FT=0;
    pth = pth /100;
    pl= pl /100;
    pt=pt ;
    FT = 100/pt;
    //LT= 1/FT;
    if (s_chunck==1)
    {
    	LT = (pt*1000000)/10000000000;
    	printf("100000000\t%c\t%d\t%lld\t%Lf\n",love, th_num, s_chunck,LT);
    }
    else

	printf("100000000\t%c\t%d\t%lld\t%Lf\n",love, th_num, s_chunck,FT);

	return 0;
}



