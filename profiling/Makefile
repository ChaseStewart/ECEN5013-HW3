CC=gcc

CFLAGS= -g -std=c99 -Werror -Wall -pthread


all: fork_vs_exec pthread_create kthread_create

fork_vs_exec:
	$(CC) $(CFLAGS) src/profile_fork_exec.c $(LIBS) -o fork_exec 
	@echo
	@echo Built Fork_Exec

pthread_create:
	$(CC) $(CFLAGS) src/profile_pthread.c $(LIBS) -o pthread_create 
	@echo
	@echo Built pThread_Create

kthread_create:
	@echo
	@echo For Kthread, use the Makefile in the kthread/ folder to create a kernel module

.PHONY: clean

clean:
	@rm -vf fork_exec pthread_create 
	@echo All functions removed!
