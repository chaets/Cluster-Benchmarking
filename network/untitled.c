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
int g_threadnum, G=100;
long double thr_put= 0;
long double latency= 0;
float p_time[100], pt=0;
float p_throuput[100],pth=0;
float p_latenency[100],pl=0;


void memoryalloc();
void memoryRandalloc();
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

void memoryRandalloc()
{
	long int i,j,ITR;
	bigptr = (char*) calloc(1073741824 ,sizeof (char));

	ptr = (char*) calloc(1073741824 ,sizeof (char));
				//memset(*ptr, 'a', 1024*sizeof(char));
				memset(ptr, 'a', 1073741824*sizeof(char));
				// memset(bigptr, 'a', 1073741824*sizeof(char));
				// ptr[0] = 'a';
				// ptr[1] =  'b';
				if (ptr == NULL)
				{
				  printf("Could not allocate memory\n");
				  exit(-1);
				}
				else
				  {
				  	printf("Memory allocated successfully.\n");
				  	ITR=((1024*1024*1024)/(g_threadnum*s_chunck));
				  	// printf("number of iteration %ld\n", ITR);
				  	for (int i = 0; i < (ITR); )
						{
						  // printf("%d\n", i);
						  j = rand_interval(ITR);
						  // printf("%ld\n", j);
						  memcpy(&bigptr[j], &ptr[j], s_chunck);
						  i = i+s_chunck;
						}
				  	// return(*ptr);
				  }
				free(ptr);
	
	free(bigptr);

}


void memoryalloc()
{
	long int i,j,ITR;

	bigptr = (char*) calloc(1073741824 ,sizeof (char));
	ptr = (char*) calloc(1073741824 ,sizeof (char));
				//memset(*ptr, 'a', 1024*sizeof(char));
				memset(ptr, 'a', 1073741824*sizeof(char));
				// ptr[0] = 'a';
				// ptr[1] =  'b';
				if (ptr == NULL)
				{
				  printf("Could not allocate memory\n");
				  exit(-1);
				}
				else
				  {
				  	printf("Memory allocated successfully.\n");
				  	ITR=((1024*1024*1024)/(g_threadnum*s_chunck));
				  	// printf("number of iteration %ld\n", ITR);
				  	for (int i = 0; i < (ITR); )
						{
						  // printf("%d\n", i);
						  
						  memcpy(&bigptr[i], &ptr[i], s_chunck);
						  // printf("%c\n", bigptr[i]);
						  // printf("%c\n", bigptr[i+1]);
						  
						  i = i+s_chunck;
						}
				  	// return(*ptr);
				  }
				free(ptr);
	
	free(bigptr);

}
// void memorybigblockSEQ()
// {
// 	char *ptrbig = (char*) calloc(1073741824 ,sizeof (char));

// }



// }
void *workSEQ(void *args)
{
	long tid, local_var;
	tid = (long) args;
	pthread_mutex_lock(&mutex);
	local_var = shared_var++;
	// printf("%c\n", memoryalloc(2));
	memoryalloc();
	pthread_mutex_unlock(&mutex);
	printf("Thread %ld got %ld\n", tid, local_var);
	pthread_exit(NULL);
}
void *workRAND(void *args)
{
	long tid, local_var;
	tid = (long) args;
	pthread_mutex_lock(&mutex);
	local_var = shared_var++;
	memoryRandalloc();
	pthread_mutex_unlock(&mutex);
	printf("Thread %ld got %ld\n", tid, local_var);
	pthread_exit(NULL);
}
void threadwork(char type, int NUM_THREADS, long long int a)
{
 	pthread_t threads[NUM_THREADS]; long tid; int rc;
 	pthread_mutex_init(&mutex, NULL); shared_var = 0;
 	struct timeval  start, end;
    gettimeofday(&start, NULL);
    
	    switch(type) 
	    {


	       case 'R' :
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


	        case 'S'  :
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
		}
	gettimeofday(&end, NULL);
    printf("elapsed: %fs\n", (float) (end.tv_usec - start.tv_usec) / 1000000 +(float) (end.tv_sec - start.tv_sec));
    p_time[G]= (float) (end.tv_usec - start.tv_usec) / 1000000 +(float) (end.tv_sec - start.tv_sec);
    thr_put= 1073741824/(((float) (end.tv_usec - start.tv_usec) / 1000000 +(float) (end.tv_sec - start.tv_sec))*1024*1024*1024);
    p_throuput[G]= thr_put;
    printf("Throughput of system is %Lf GB/Sec\n", thr_put );

    if (s_chunck==1)
    {
    	latency = (((float) (end.tv_usec - start.tv_usec) / 1000000 +(float) (end.tv_sec - start.tv_sec))*1000000)/1073741824;
    	printf("Latency of system is %Lf Microseconds\n", latency );
    	p_latenency[G]= latency;
    }
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

	

    printf(" I love you %s\n", argv[1]);
    fp = fopen(argv[1], "r");

    if (fp == NULL)
        exit(EXIT_FAILURE);
// printf(" I love you \n");
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
    // printf(" I love you %d\n", th_num);
    // printf(" I love you charc%c\n", love);

    for(G=0; G<100;G++)
    {
    	threadwork(love, th_num, B_size);
    	pl= pl + p_latenency[G];
    	pth = pth + p_throuput[G];
    	pt=pt + p_time[G];


    }
    pth = pth /100;
    pl= pl /100;
    pt=pt /100;
    // threadwork(love, th_num, B_size);
    // printf(" I love you osam %d\n", th_num);
    printf("Time %f Throughput %f Latency %f \n", pt, pth, pl);

	return 0;
}






