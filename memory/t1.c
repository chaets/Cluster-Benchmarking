#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

// unsigned int rand_interval(unsigned int max)
// {
//     unsigned long
//     // max <= RAND_MAX < ULONG_MAX, so this is okay.
//     num_bins = (unsigned long) max + 1,
//     num_rand = (unsigned long) RAND_MAX + 1,
//     bin_size = num_rand / num_bins,
//     defect   = num_rand % num_bins;

//   long x;
//   do {
//    x = random();
//   }
//   // This is carefully written not to overflow
//   while (num_rand - defect <= (unsigned long)x);

//   // Truncated division is intentional
//   return x/bin_size;
// }


int main(int argc, char **argv) {


  int sz, fd;
  char *ptr;
  int s_chunck = 1024; 
    // bigptr = (char*) calloc(1073741824 ,sizeof (char));
    ptr = (char*) calloc(s_chunck ,sizeof (char));
    memset(ptr, 'a', s_chunck*sizeof(char));

    fd = open("~/temp/foo.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
    {
     perror("r1");
     exit(1);
    }
    for (int i = 0; i < iteration; i++)
    {
        sz = write(fd, ptr, s_chunck);
    }
    

    // printf("called write(% d, \"hello geeks\\n\", %d)."    " It returned %d\n", fd, strlen("hello geeks\n"), sz);

    close(fd);
      // 

  return 0;
}






FILE * fp;
    // char * line = NULL;
    // size_t len = 0;
    // ssize_t read;
    // int l_no=0;
    // char str[3][10];
    // char * type = NULL;
    // char * thread_num = NULL;
    // char * size = NULL;
    // long long int  B_size;
    // int th_num;




    // fp = fopen(argv[1], "r");
    // if (fp == NULL)
    //     exit(EXIT_FAILURE);

    // while ((read = getline(&line, &len, fp)) != -1) {

    //   if (l_no==0)
    //     {
          
    //       type=line;
    //       printf(" line num 0 %c\n", type[2]);
          
    //     }
    //     else if (l_no==1)
    //       {
    //          size=line;
    //         printf(" line num 1 %s\n", size);
    //         B_size= atoi(size);
    //         printf(" Block size %lld\n", B_size);
    //       }
    //     else if (l_no==2)
    //     {
    //       thread_num=line;
    //       printf(" line number 2 %s\n", thread_num);
    //       th_num= atoi(thread_num);
    //       printf(" Thread number %d\n", th_num);
    //     }
    //     l_no++;

    // }

    // fclose(fp);
    // if (line)
    //     free(line);
    // exit(EXIT_SUCCESS);





// for(int i=0;i<exec_iteration_gb;i+=atoi(global_argv_ram[2])){
//     r1=rand()%(exec_iteration_gb - atoi(global_argv_ram[2]));
//     memcpy(&write_mem[r1],&read_mem[r1],atoi(global_argv_ram[2]));
//   }






// int j;
//   /* Initialize the two argument vectors */
// char *bigptr = (char*) calloc(100 ,sizeof (char));
// int r1;
// char *ptr = (char*) calloc(100 ,sizeof (char));
// memset(ptr, 'a', 100*sizeof(char));

// for (int i = 0; i < 10; i++)
// {
//   j = rand_interval(100);
//   //printf("%d\n",j );
//   memcpy(&bigptr[j], &ptr[j], 10);
//   printf("%c\t%c\n", bigptr[j], bigptr[j+5]);






//   // printf("%cRAM\n", bigptr[i]);
//   //if (i%10==0)
//   //{
//     /* code */
  
//   //printf("%c\n", ptr[i]);
//     // r1=rand()%(120);
//     // printf("%d\n",r1 );
//     // memcpy(&bigptr[r1], &ptr[r1], 10);
//   //printf("%c\n", bigptr[i]);
//   //}
//   //printf("BIGPTR\t%c\t%c\t%ld\n", *bigptr, bigptr[i], &bigptr[i] );
// }
// // for (int i = 0; i < 100; ++i)
// // {
// //   printf("%c\n", bigptr[i]);
// // }
// free(bigptr);
// free(ptr);


























// printf("memset end\n");


// // for (int i = 0; i < 100; ++i)
// // {
// //   memset(bigptr, 'a', 10*sizeof(char));
// //   bigptr= bigptr+10;

// // }
// for (int i = 0; i < 100; i++)
// {
//   memcpy(bigptr, ptr, sizeof*ptr);

//   printf("PTR\t%c\t%x\t%d\n", *ptr, ptr, &ptr );
//   wait(1);
//   printf("BIGPTR\t%c\t%x\t%d\n", *bigptr, bigptr, &bigptr );
//   bigptr = bigptr+10;
//   ptr = ptr + 10;
// }
// printf("menmcopy end\n");
// for (int i = 0; i < 1000; ++i)
// {
//   printf("%c ", *bigptr);
//   bigptr= bigptr+1;
  
// }

// printf("end\n");
