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
#include <stdio.h>
#include <stdlib.h>

int  main(int argc, char const *argv[])
{
	int i=0;

	char * port[4];
	int j = 11155;
	char buffer[20];

	// itoa(j,buffer,10);
	snprintf(buffer, sizeof(buffer), "%d", j);
	printf("%s\n", buffer );

	printf("iloveyou\n");

	port[0]=buffer;
	// port[1]= "1115";
	// port[2]= "11155";
	// port[3]= "11155";

	// char * pc = "11155 11156 11157 11158";
 //    // pc[i] = (char)port[i];
    printf("%s\n",port[0] );
 //    printf("%s\n", pc[1]);
 //    i++;
	/* code */
	return 0;
}