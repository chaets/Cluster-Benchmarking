CC=gcc
CFLAGS=-g -Wall -O2 -lpthread

all:
	$(CC) $(CFLAGS) -o MyNETBench-TCP MyNETBench-TCP.c
	$(CC) $(CFLAGS) -o MyNETBench-UDP MyNETBench-UDP.c

clean:
	$(RM) *.o MyNETBench-TCP MyNETBench-UDP
