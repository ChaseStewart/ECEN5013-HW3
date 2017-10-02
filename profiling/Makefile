CC=gcc

CFLAGS= -g -std=c99 -Werror -Wall -pthread

IPATH  = -I./inc 
IPATH += -I../../Unity/src
IPATH += -I./test

LIBS=

FILES  = create_fork_vs_exec.c
FILES += 

all: fork_vs_exec pthread_create kthread_create

fork_vs_exec:
	$(CC) $(CFLAGS) $(IPATH) src/create_fork_vs_exec.c $(LIBS) -o fork_vs_exec 
	@echo Built Fork_vs_Exec

pthread_create:
	$(CC) $(CFLAGS) $(IPATH) src/create_pthread.c $(LIBS) -o pthread_create 
	@echo Built pThread_Create

kthread_create:
	$(CC) $(CFLAGS) $(IPATH) src/create_kthread.c $(LIBS) -o kthread_create 
	@echo Built kThread_Create

.PHONY: clean

clean:
	@rm -vf fork_vs_exec pthread_create kthread_create
	@echo All functions removed!
