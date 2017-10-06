/*****************************************************
 * Redistribution, modification or use of this software in source or binary forms 
 * is permitted as long as the files maintain this copyright. Users are permitted to 
 * modify this and use it to learn about the field of embedded software but don't copy 
 * my (Chase E Stewart's) work for class, I worked really hard on this. Alex Fosdick and 
 * the University of Colorado and Chase E Stewart are not liable for any misuse of this material. 
 * License copyright (C) 2017 originally from Alex Fosdick, code by Chase E Stewart.
 *****************************************************/
/**
 * @file pthread_example.c
 * @brief A short program to demonstrate pthread functions
 * 
 * 
 * @author Chase E Stewart
 * @date October 5 2017
 * @version 1.1
 *
 */

/* this is required for proper use of pthread_getattr_* and pthread_setattr_* */
#define _GNU_SOURCE

#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <pthread.h>


/*
 * @brief have thread take input value and print it 
 *
 * @param void  *input_val - input val to print within thread 
 *
 * @return void *- a void pointer to whatever the pthread wants to return, 
 * received by the caller of pthread_join(). In our simple case this is NULL; 
 */
void *pthread_example_1(void *input_val)
{
	int thread_id;
	int *input = (int *)input_val;
	printf("[demo-pthread][thread1] Thread 1 initialized with input value of %d\n", *input);
	printf("[demo-pthread][thread1] using pthread_self() to retrieve pthread_id\n");
	thread_id = pthread_self();
	printf("[demo-pthread][thread1] Hello from thread-id %u!\n", thread_id);

	printf("[demo-pthread][thread1] exiting via simple return from thread main is OK, returning NULL \n");
	return NULL;
}

/*
 * @brief have thread take input value and print it 
 *
 * @param void  *input_val - input val to print within thread 
 *
 * @return void *- a void pointer to whatever the pthread wants to return, 
 * received by the caller of pthread_join(). In our simple case this is NULL; 
 */
void *pthread_example_2(void *void_tid)
{
	long int status;	
	printf("[demo-pthread][thread2] Thread 2 initialized with input value of NULL\n"); 
	status = 2;
	printf("[demo-pthread][thread2] Exiting via pthread_exit(), returning status %ld to joining process \n", status);
	pthread_exit((void *) status);
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
	pthread_attr_t set_new_default, get_new_default;
	size_t my_guardsize, my_stacksize;
	int passed_in;
	void *thread2_retval;

	printf("[demo-pthread][main] this program will demonstrate pthread_create, pthread_join, \npthread_exit, pthread_self, pthread_getattr_np, pthread_getattr_default_np, pthread_setattr_np\n\n");

	/* call pthread_create with default attrs, pass it in a value */
	passed_in = 10;
	printf("[demo-pthread][main] Creating thread1 with default attrs via pthread_create() with passed-in arg of %d \n", passed_in);
	if(pthread_create(&my_thread_1, NULL, pthread_example_1, &passed_in) != 0)
	{
		printf("[demo-pthread][main] failed to create pthread\n");
		return 1;
	}

	/* get thread1's default attrs, print them, and modify them */
	printf("[demo-pthread][main] populating pthread_attr_t with default attrs of thread1 via pthread_getattr_np()\n");
	pthread_getattr_np(my_thread_1, &set_new_default);
	pthread_attr_getguardsize(&set_new_default, &my_guardsize);
	pthread_attr_getstacksize(&set_new_default, &my_stacksize);
	printf("[demo-pthread][main] Guardsize: %ld, stacksize: %ld from original default\n", my_guardsize, my_stacksize);
	
	printf("[demo-pthread][main] changing default attr guardsize to 8192 from 4096 using pthread_setattr_setguardsize()\n");
	pthread_attr_setguardsize(&set_new_default, (size_t) 8192);
	pthread_attr_getguardsize(&set_new_default, &my_guardsize);
	pthread_attr_getstacksize(&set_new_default, &my_stacksize);
	printf("[demo-pthread][main] Guardsize: %ld, stacksize: %ld guard should be set to 8192\n", my_guardsize, my_stacksize);

		
	/* create default pthread_attr_t, and explicitly pass it to thread2 upon pthread_create() */
	printf("[demo-pthread][main] Now create an pthread_attr_t with default attrs to pass into thread 2 using pthread_attr_init() and pthread_getattr_default_np()\n");
	pthread_attr_init(&get_new_default);
	pthread_setattr_default_np(&get_new_default);
	
	/* call pthread_create and have it run my_hello above */
	printf("[demo-pthread][main] create thread2 with pthread_create() and an expicit pthread_attr_t rather than null \n"); 
	if(pthread_create(&my_thread_2, &get_new_default, pthread_example_2, NULL) != 0)
	{
		printf("[demo-pthread][main] failed to create pthread\n");
		return 1;
	}
	/* have main process wait to join w/ created pthread*/
	if (pthread_join(my_thread_1, NULL) != 0)
	{
		printf("[demo-pthread][main] failed to join with pthread\n");
		return 1;
	}
	printf("[demo-pthread][main] Join with thread1 via pthread_join() received retval of NULL\n");

	/* have main process wait to join w/ created pthread*/
	if (pthread_join(my_thread_2, &thread2_retval) != 0)
	{
		printf("[demo-pthread][main] failed to join with pthread\n");
		return 1;
	}
	printf("[demo-pthread][main] Joined with thread2, received retval of %ld \n", (long int) thread2_retval);
	
	printf("[demo-pthread][main] Complete- exiting!\n");
	return 0;
}


