CC=gcc

CFLAGS= -g -std=c99 -Werror -Wall -pthread


all: fork_vs_exec pthread_create kthread_create

fork_vs_exec:
	$(CC) $(CFLAGS) src/create_fork_exec.c $(LIBS) -o fork_exec 
	@echo Built Fork_Exec

pthread_create:
	$(CC) $(CFLAGS) src/create_pthread.c $(LIBS) -o pthread_create 
	@echo Built pThread_Create

kthread_create:
	$(CC) $(CFLAGS) src/create_kthread.c $(LIBS) -o kthread_create 
	@echo Built kThread_Create

.PHONY: clean

clean:
	@rm -vf fork_exec pthread_create kthread_create
	@echo All functions removed!
