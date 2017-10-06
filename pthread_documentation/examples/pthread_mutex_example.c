/*****************************************************
 * Redistribution, modification or use of this software in source or binary forms 
 * is permitted as long as the files maintain this copyright. Users are permitted to 
 * modify this and use it to learn about the field of embedded software but don't copy 
 * my (Chase E Stewart's) work for class, I worked really hard on this. Alex Fosdick and 
 * the University of Colorado and Chase E Stewart are not liable for any misuse of this material. 
 * License copyright (C) 2017 originally from Alex Fosdick, code by Chase E Stewart.
 *****************************************************/
/**
 * @file profile_example.c
 * @brief A short program to demonstrate pthread functions
 * 
 * 
 * @author Chase E Stewart
 * @date October 5 2017
 * @version 1.1
 *
 */
#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <pthread.h>

static pthread_mutex_t my_mutex;

/*
 * @brief short task for thread to do,  
 * have thread get tid via self() then print it and die 
 *
 * @param void  *void_tid - unused, but pthread_create passes in a void * 
 *
 * @return void *- a void pointer to whatever the pthread wants to return, 
 * received by the caller of pthread_join(). In our simple case this is NULL; 
 */
void *pthread_example(void *void_tid)
{
	int status;
	printf("[demo-pthread-mutex][thread1] Initialize thread1\n");
	printf("[demo-pthread-mutex][thread1] pthread_mutex_trylock() will instantly fail bc main has the lock\n");
	status = pthread_mutex_trylock(&my_mutex);
	if (status != 0)
	{
		printf("[demo-pthread-mutex][thread1] Trylock failed!\n");
	}
	
	printf("[demo-pthread-mutex][thread1] Now running mutex_lock- it will block until main releases it \n");
	pthread_mutex_lock(&my_mutex);
	printf("[demo-pthread-mutex][thread1] Got the lock!\n");
	pthread_mutex_unlock(&my_mutex);
	printf("[demo-pthread-mutex][thread1] Released the lock!\n");
	printf("[demo-pthread-mutex][thread1] Exiting!\n"); 
	return NULL;
}

void *pthread_example_2(void *void_tid)
{
	int status = 2;
	
	printf("[demo-pthread-mutex][thread 2] Exiting with status %d \n", status);
	pthread_exit((void *)&status);
}


/*
 * @brief demonstrate pthread functions with printouts to explain 
 *
 * @param void 
 *
 * @return int- return status of the function 
 */
int main(void)
{
	pthread_t my_thread_1;
	printf("[demo-pthread-mutex][main] This program will demonstrate mutex_init, mutex_lock, mutex_destroy, mutex_lock, mutex_trylock, mutex_unlock\n");

		
	printf("[demo-pthread-mutex][main] initialize mutex w default parameters\n");
	pthread_mutex_init(&my_mutex, NULL);


	printf("[demo-pthread-mutex][main] now lock the mutex for 5 seconds before spawning threads\n");
	pthread_mutex_lock(&my_mutex);

	/* call pthread_create and have it run my_hello above */
	if(pthread_create(&my_thread_1, NULL, pthread_example, NULL) != 0)
	{
		printf("[demo-pthread-mutex][main] failed to create pthread\n");
		return 1;
	}
	sleep(5);
	printf("[demo-pthread-mutex][main] now releasing the mutex\n");
	pthread_mutex_unlock(&my_mutex);

	/* have main process wait to join w/ created pthread*/
	if (pthread_join(my_thread_1, NULL) != 0)
	{
		printf("[demo-pthread-mutex][main] failed to join with pthread\n");
		return 1;
	}
		printf("[demo-pthread-mutex][main] joined with thread1\n");
	
	printf("[demo-pthread-mutex][main] destroy mutex\n");
	pthread_mutex_destroy(&my_mutex);
	
	printf("[demo-pthread-mutex] Complete- exiting!\n");
	return 0;
}


