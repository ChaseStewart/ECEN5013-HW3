#include <time.h>
#include <stdint.h>
#include <stdio.h>
#include <pthread.h>


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


int main(void)
{
	clock_t pthread_start, pthread_end;
	double pthread_time;
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
	pthread_time = (float) pthread_end - (float) pthread_start;
	printf("[profile-pthread][main] pthread CPU time was %f ", pthread_time);
	return 0;
}

