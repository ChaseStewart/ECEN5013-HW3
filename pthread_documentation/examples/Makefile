CC=gcc
CFLAGS= -g -Werror -Wall -pthread 

all: pthread pthread_cond pthread_mutex

pthread:
	$(CC) $(CFLAGS) pthread_example.c -o pthread_example
	@echo build pthread_example complete 
	@echo
pthread_cond:
	$(CC) $(CFLAGS) pthread_cond_example.c -o pthread_cond_example
	@echo build pthread_cond_example complete 
	@echo

pthread_mutex:
	$(CC) $(CFLAGS) pthread_mutex_example.c -o pthread_mutex_example
	@echo build pthread_mutex_example complete 
	@echo


.PHONY: clean

clean:
	@rm -vf pthread_example pthread_cond_example pthread_mutex_example
	@echo All executables removed!

