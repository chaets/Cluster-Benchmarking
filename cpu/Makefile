CC = gcc
CFLAGS = -Wall -lpthread -O2

clean:
	rm -rf *.o main

all: clean
	$(CC) $(CFLAGS) -mavx -pthread main.c -o main

