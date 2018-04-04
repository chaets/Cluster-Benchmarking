switch (k)
	{
		case 1 :
			{
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
				  	printf("Memory allocated successfully.%c\n ", ptr[0]);
				  	for (int i = 0; i < (1073741824/g_threadnum); )
						{
						  printf("%d\n", i);
						  
						  memcpy(&bigptr[i], &ptr[i], 1024);
						  printf("%c\n", bigptr[i]);
						  printf("%c\n", bigptr[i+1]);
						  
						  i = i+s_chunck;
						}
				  	// return(*ptr);
				  }
				free(ptr);
				break;
			}
		case 2 :
			{	
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
				  	printf("Memory allocated successfully.%c\n ", ptr[0]);
				  	for (int i = 0; i < (1073741824/g_threadnum); )
						{
						  printf("%d\n", i);
						  
						  memcpy(&bigptr[i], &ptr[i], 1024);
						  printf("%c\n", bigptr[i]);
						  printf("%c\n", bigptr[i+1]);
						  
						  i = i+s_chunck;
						}
				  	// return(*ptr);
				  }
				free(ptr);
				break;
			}
		case 3 :
			{
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
				  	printf("Memory allocated successfully.%c\n ", ptr[0]);
				  	for (int i = 0; i < (1073741824/g_threadnum); )
						{
						  printf("%d\n", i);
						  
						  memcpy(&bigptr[i], &ptr[i], 1024);
						  printf("%c\n", bigptr[i]);
						  printf("%c\n", bigptr[i+1]);
						  
						  i = i+s_chunck;
						}
				  	// return(*ptr);
				  }
				free(ptr);
				break;
			}
	}





	Random

	switch (k)
	{
		case 1 :
			{
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
				  	printf("Memory allocated successfully.%c\n ", ptr[0]);
				  	for (int i = 0; i < (1073741824/g_threadnum); )
						{
						  // printf("%d\n", i);
						  j = rand_interval(1073741824/g_threadnum);
						  printf("%ld\n", j);
						  memcpy(&bigptr[j], &ptr[j], s_chunck);
						  i = i+s_chunck;
						}
				  	// return(*ptr);
				  }
				free(ptr);
				break;
			}
		case 2 :
			{	
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
				  	printf("Memory allocated successfully.%c\n ", ptr[0]);
				  	for (int i = 0; i < (1073741824/g_threadnum); )
						{
						  // printf("%d\n", i);
						  j = rand_interval(1073741824/g_threadnum);
						  printf("%ld\n", j);
						  memcpy(&bigptr[j], &ptr[j], s_chunck);
						  i = i+s_chunck;
						}
				  	// return(*ptr);
				  }
				free(ptr);
				break;
			}
		case 3 :
			{
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
				  	printf("Memory allocated successfully.%c\n ", ptr[0]);
				  	for (int i = 0; i < (1073741824/g_threadnum); )
						{
						  // printf("%d\n", i);
						  j = rand_interval(1073741824/g_threadnum);
						  printf("%ld\n", j);
						  memcpy(&bigptr[j], &ptr[j], s_chunck);
						  i = i+s_chunck;
						}
				  	// return(*ptr);
				  }
				free(ptr);
				break;
			}
	}