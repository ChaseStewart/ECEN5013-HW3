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
void *pthread_example(void *void_tid)
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

void *pthread_example_2(void *void_tid)
{
	int status = 2;
	
	printf("[profile-pthread][thread 2] Exiting with status %d \n", status);
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
	pthread_t my_thread_1, my_thread_2;

	/* call pthread_create and have it run my_hello above */
	if(pthread_create(&my_thread_1, NULL, pthread_example, NULL) != 0)
	{
		printf("[profile-pthread][main] failed to create pthread\n");
		return 1;
	}
	/* call pthread_create and have it run my_hello above */
	if(pthread_create(&my_thread_2, NULL, pthread_example_2, NULL) != 0)
	{
		printf("[profile-pthread][main] failed to create pthread\n");
		return 1;
	}

	/* have main process wait to join w/ created pthread*/
	if (pthread_join(my_thread_2, NULL) != 0)
	{
		printf("[profile-pthread][main] failed to join with pthread\n");
		return 1;
	}
	
	/* have main process wait to join w/ created pthread*/
	if (pthread_join(my_thread_1, NULL) != 0)
	{
		printf("[profile-pthread][main] failed to join with pthread\n");
		return 1;
	}
	
	printf("[demo-pthread] Complete- exiting!\n");
	return 0;
}


