CC=gcc

CFLAGS= -g -std=c99 -Werror -Wall -pthread

all: 
	$(CC) $(CFLAGS) multithread_io.c -o multithread_io 
	@echo Built Multi-Thread IO

.PHONY: clean

clean:
	@rm -vf multithread_io
	@echo All functions removed!
