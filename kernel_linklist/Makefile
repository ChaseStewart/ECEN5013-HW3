CC=gcc

CFLAGS= -g -std=c99 -Werror -Wall -pthread

IPATH  = -I./inc 
IPATH += -I../../Unity/src
IPATH += -I./test

LIBS=

all: 
	$(CC) $(CFLAGS) $(IPATH) get_kthreads.c $(LIBS) -o get_kthreads
	@echo Built get_kthreads

.PHONY: clean

clean:
	@rm -vf fork_vs_exec pthread_create kthread_create
	@echo All functions removed!
