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

	/* call pthread_create */
	if(pthread_create(&my_thread, NULL, my_hello, &thread_id) != 0)
	{
		printf("[profile-pthread][main] failed to create pthread\n");
		return 1;
	}

	if (pthread_join(my_thread, NULL) != 0)
	{
		printf("[profile-pthread][main] failed to join with pthread\n");
		return 1;
	}
	printf("[profile-pthread][main] thread actions complete\n");
	pthread_end=clock();
	if (pthread_end == (clock_t)-1)
	{
		/* failed to get CPU ticks */
		printf("[profile-pthread][main] failed to get pthread_end time\n");
	}

	pthread_time = pthread_end - pthread_start;
	printf("[profile-pthread][main] pthread CPU time was %f ", pthread_time);

}

