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

static pthread_cond_t example_cv;
static pthread_mutex_t example_cv_mutex;

/*
 * @brief short task for thread to do,  
 * have thread get tid via self() then print it and die 
 *
 * @param void  *void_tid - unused, but pthread_create passes in a void * 
 *
 * @return void *- a void pointer to whatever the pthread wants to return, 
 * received by the caller of pthread_join(). In our simple case this is NULL; 
 */
void *pthread_cond_example(void *unused)
{
	printf("[demo-pthread-cond][thread 1] thread1 created\n");
	printf("[demo-pthread-cond][thread 1] pthread_cond_wait() for CV signal\n");
	pthread_cond_wait(&example_cv, &example_cv_mutex);	
	printf("[demo-pthread-cond][thread 1] woke up from cond_wait\n");
	printf("[demo-pthread-cond][thread 1] now will exit\n");
	
	pthread_exit(NULL);
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
	
	printf("[demo-pthread-cond][main] This program will demo cond_init, cond_signal, cond_wait, cond_destroy\n");

	printf("[demo-pthread-cond][main] Initializing CV with pthread_cond_init() \n");
	pthread_cond_init(&example_cv, NULL);
	
	printf("[demo-pthread-cond][main] Initializing CV-mutex\n");
	pthread_mutex_init(&example_cv_mutex, NULL);

	/* call pthread_create and have it run my_hello above */
	if(pthread_create(&my_thread_1, NULL, pthread_cond_example, NULL) != 0)
	{
		printf("[demo-pthread-cond][main] failed to create pthread\n");
		return 1;
	}
	
	/* wait and then signal thread1 */
	printf("[demo-pthread-cond][main] sleeping 5 seconds before signaling CV\n");
	sleep(5);
	pthread_cond_signal(&example_cv);
	printf("[demo-pthread-cond][main] sent CV signal via pthread_cond_signa()\n");

	printf("[demo-pthread-cond][main] blocked on join w/ thread1\n");
	/* have main process wait to join w/ created pthread*/
	if (pthread_join(my_thread_1, NULL) != 0)
	{
		printf("[demo-pthread-cond][main] failed to join with pthread\n");
		return 1;
	}
	printf("[demo-pthread-cond][main] joined w/ thread1\n");
	

	/* Now destroy conditional variable */	
	printf("[demo-pthread-cond][main] Destroying CV with pthread_cond_destroy()\n");
	pthread_cond_destroy(&example_cv);
	printf("[demo-pthread-cond][main] Destroying CV-mutex with pthread_mutex_destroy()\n");
	pthread_mutex_destroy(&example_cv_mutex);
	
	printf("[demo-pthread-cond] Complete- exiting!\n");
	return 0;
}


