#include <time.h>
#include <stdint.h>
#include <stdio.h>

clock_t pthread_start, pthread_end;
double pthread_time;



int main(void){
	pthread_start=clock();
	if (pthread_start == (clock_t)-1)
	{
		/* failed to get CPU ticks */
	}

	/* call pthread_create */

	pthread_end=clock();
	if (pthread_start == (clock_t)-1)
	{
		/* failed to get CPU ticks */
	}

	pthread_time = pthread_end - pthread_start;
	printf("[pthread] pthread CPU time was %f ", pthread_time);

}

