/*****************************************************
 * Redistribution, modification or use of this software in source or binary forms 
 * is permitted as long as the files maintain this copyright. Users are permitted to 
 * modify this and use it to learn about the field of embedded software but don't copy 
 * my (Chase E Stewart's) work for class, I worked really hard on this. Alex Fosdick and 
 * the University of Colorado and Chase E Stewart are not liable for any misuse of this material. 
 * License copyright (C) 2017 originally from Alex Fosdick, code by Chase E Stewart.
 *****************************************************/
/**
 * @file profile_pthread.c
 * @brief A short program to profile a new child created via pthread_create()
 * 
 * this program uses processor time via time.h and clock() rather than human-time. 
 * 
 * @author Chase E Stewart
 * @date October 5 2017
 * @version 1.1
 *
 */
#include <time.h>
#include <stdint.h>
#include <stdio.h>
#include <pthread.h>

/*
 * @brief short task for thread to do,  
 * have thread get tid via self() then print it and die 
 *
 * @param void  *void_tid - unused, but pthread_create passes in a void * 
 *
 * @return void *- a void pointer to whatever the pthread wants to return, 
 * received by the caller of pthread_join(). In our simple case this is NULL; 
 */
void *my_hello(void *void_tid)
{
	int thread_id;
	int *tid_ptr = (int *)void_tid;
	
	thread_id = pthread_self();
	if (thread_id != 0)
	{
		printf("[profile-pthread][thread %d] Hello from thread %d\n", thread_id, thread_id);
		*tid_ptr = thread_id;
	}
	return NULL;
}


/*
 * @brief catch clock start time, then call pthread_create() to make a thread do my_hello()
 * have parent process wait to pthread_join() on child, then stop clock
 * return the delta time to stdout 
 *
 * @param void 
 *
 * @return int- return status of the function 
 */
int main(void)
{
	clock_t pthread_start, pthread_end;
	long int pthread_time;
	pthread_t my_thread;
	int thread_id;

	pthread_start=clock();
	if (pthread_start == (clock_t)-1)
	{
		/* failed to get CPU ticks */
		printf("[profile-pthread][main] failed to get pthread_start time\n");
	}

	/* call pthread_create and have it run my_hello above */
	if(pthread_create(&my_thread, NULL, my_hello, &thread_id) != 0)
	{
		printf("[profile-pthread][main] failed to create pthread\n");
		return 1;
	}

	/* have main process wait to join w/ created pthread*/
	if (pthread_join(my_thread, NULL) != 0)
	{
		printf("[profile-pthread][main] failed to join with pthread\n");
		return 1;
	}
	
	/* once main process joins with thread, stop the clock and rint results*/
	pthread_end=clock();
	printf("[profile-pthread][main] thread actions complete\n");
	if (pthread_end == (clock_t)-1)
	{
		/* failed to get CPU ticks */
		printf("[profile-pthread][main] failed to get pthread_end time\n");
	}

	/* calculate and print delta time */
	pthread_time = pthread_end - pthread_start;
	printf("[profile-pthread][main] pthread CPU time was %ld\n", pthread_time);
	return 0;
}

