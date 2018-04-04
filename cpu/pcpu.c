#include<stdio.h>
//#include<chrono>
//#include<iostream>
#include<stdlib.h>
#include<string.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

//#include<>
//#include <sys/time.h>
#include <time.h>

#define ITERATIONS 100000

long iterations=ITERATIONS;
//#include<cstdio>
/* char precision[2];
char noOfThreads[2]; */

void threadFunction(char ,int);
void *SP_Trillion(void *arg);
void *DP_Trillion(void *arg);
void *QP_Trillion(void *arg);
void *HP_Trillion(void *arg);


void threadFunction(char Precision,int noOfThreads){

	int i;
	int numberOfThreads;
	pthread_t th[10];
	clock_t start, end;
	int Flops;
	int gFlops;
	int cpu_time_used;
	
	int iterationsPerThread=ITERATIONS/numberOfThreads;

 		
		printf("djfhjdshfjsdssjkasjscsd\n");
		
		if(!strcmp(Precision,"SP")){
		// SP_Trilion(NULL); 
		printf("fdkkfj");
 		numberOfThreads=noOfThreads;
		start = clock();
		for(i=1;i<=numberOfThreads;i++)
		{
			pthread_create(&th[i],NULL,SP_Trillion,(void *) iterationsPerThread);
			pthread_join(th[i], NULL);
		}
		pthread_exit(NULL);
		end = clock();
		cpu_time_used = ((double) (end - start)); //CLOCKS_PER_SEC;

		printf("\nTime: %d s\n",cpu_time_used);

		Flops=(ITERATIONS)/(double)(cpu_time_used);

		gFlops=(double)Flops/1000000000;// Calculate Giga Flops Formula: F lops * 10raised to (-9).

		printf("GFLOPS of the CPU SP: %d\n",gFlops);	
		}
		
		
		else if(Precision=='DP'){
		//	DP_Trilion(NULL);
		numberOfThreads=noOfThreads;

		start = clock();

		for(i=1;i<=numberOfThreads;i++)
		{
			pthread_create(&th[i],NULL,DP_Trillion,(void *) iterationsPerThread);
			pthread_join(th[i], NULL);
		}
		pthread_exit(NULL);
		end = clock();
		cpu_time_used = ((double) (end - start)); //CLOCKS_PER_SEC;

		printf("\nTime: %d s\n",cpu_time_used);

		Flops=(ITERATIONS)/(double)(cpu_time_used);

		gFlops=(double)Flops/1000000000;// Calculate Giga Flops Formula: F lops * 10raised to (-9).

		printf("GFLOPS of the CPU DP: %d\n",gFlops);
		
		
		}
		else if(Precision=='QP'){
		//	QP_Trilion(NULL);
		numberOfThreads=noOfThreads;
		start = clock();
		for(i=1;i<=numberOfThreads;i++)
		{
			pthread_create(&th[i],NULL,QP_Trillion,(void *) iterationsPerThread);
			pthread_join(th[i], NULL);
		}
		pthread_exit(NULL);
		end = clock();
		cpu_time_used = ((double) (end - start)); //CLOCKS_PER_SEC;

		printf("\nTime: %d s\n",cpu_time_used);

		Flops=(ITERATIONS)/(double)(cpu_time_used);

		gFlops=(double)Flops/1000000000;// Calculate Giga Flops Formula: F lops * 10raised to (-9).

		printf("GFLOPS of the CPU QP: %d\n",gFlops);
		}
	
		else if(Precision=='HP'){
		//	HP_Trilion(NULL);

		numberOfThreads=noOfThreads;
		start = clock();
		for(i=1;i<=numberOfThreads;i++)
		{
			pthread_create(&th[i],NULL,HP_Trillion,(void *) iterationsPerThread);
			pthread_join(th[i], NULL);
		}
		pthread_exit(NULL);
		end = clock();
		cpu_time_used = ((double) (end - start)); //CLOCKS_PER_SEC;

		printf("\nTime: %d s\n",cpu_time_used);

		Flops=(ITERATIONS)/(double)(cpu_time_used);

		gFlops=(double)Flops/1000000000;// Calculate Giga Flops Formula: F lops * 10raised to (-9).

		printf("GFLOPS of the CPU HP: %d\n",gFlops);
		
		
	}
	else
		printf("Invalid input");
} 
//Single Precision Operations
 void *SP_Trillion(void *arg)
{
	int a= 10;
	int b=20;
	int i;
	int iteration_per_Thread;
	
	iteration_per_Thread= (int)arg;
	
	//printf("%s",arg);

	for(i=1;i<=iteration_per_Thread;i++){

		a=a*b;

		a=a+b;

		a=a++;

		b=b++;

		a=(a+a+b)*(b*b*b);

		b=a*a;

		b=b++;

		printf("Thread 1 ");
	}
} 
//Double Precision Operations
void *DP_Trillion(void *arg){

	long a =34243242243423;
	long b=34039409309;
	int i;
	int iteration_per_Thread;
	
	iteration_per_Thread= (int)arg;

	for(i=1;i<=iteration_per_Thread;i++){

		a=a*b;

		a=a+b;

		a=a++;

		b=b++;

		a=(a+a+b)*(b*b*b);

		b=a*a;

		b=b++;
	}

}

void *HP_Trillion(void *arg){

short a=12;

short b=133;
int i;

int iteration_per_Thread;
	
	iteration_per_Thread= (int)arg;
    
	for(i=1;i<=iteration_per_Thread;i++){

		a=a*b;

		a=a+b;

		a=a++;

		b=b++;

		a=(a+a+b)*(b*b*b);

		b=a*a;

		b=b++;
	}


}

void *QP_Trillion(void *arg){
	char a='s';
	
	char b='v';
	int i;
	
	int iteration_per_Thread;
	
	iteration_per_Thread= (int)arg;
	
	for(i=1;i<=iteration_per_Thread;i++){

		a=a*b;

		a=a+b;

		a=a++;

		b=b++;

		a=(a+a+b)*(b*b*b);

		b=a*a;

		b=b++;
	}
	
	

}

int main ( int argc, char *argv[] )
{
    char precision[2];
	int noOfThreads;
	// char data[5];
	printf("Enter the file name: \n");
    //scanf
    if ( argc != 2 ) /* argc should be 2 for correct execution */
    {
        /* We print argv[0] assuming it is the program name */
        printf( "usage: %s filename", argv[0] );
    }
    else
    {
        // We assume argv[1] is a filename to open
        FILE *file = fopen( argv[1], "r" );

        /* fopen returns 0, the NULL pointer, on failure */
        if ( file == 0 )
        {
            printf( "Could not open file\n" );
        }
        else
        {
              /* Read one character at a time from file, stopping at EOF, which
               indicates the end of the file. Note that the idiom of "assign
               to a variable, check the value" used below works because
               the assignment statement evaluates to the value assigned. */
 
			while  ( EOF != fscanf(file,"%s\n%d",&precision,&noOfThreads) )
			//while (fgets(line, sizeof(line), file))
            {

			}
			printf("%s\n %d\n",precision,noOfThreads);
			printf("djfh\n");
			fclose( file );	
				
			// threadFunction(&precision,noOfThreads);
			printf("d\n");
        }
		
		
		

    }
	
	printf("djfhjdshfjsdsdsdsdsdssjkasj%s\n", precision);
	
	threadFunction(*precision,noOfThreads);
	printf("The idjfij");
	
	
	return 0;
}