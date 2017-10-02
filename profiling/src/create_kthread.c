#include <time.h>
#include <stdint.h>
#include <stdio.h>

clock_t kthread_start, kthread_end;
double kthread_time;



int main(void){
	kthread_start=clock();
	if (kthread_start == (clock_t)-1)
	{
		/* failed to get CPU ticks */
	}
	/* call kthread_create */
	kthread_end=clock();
	if (kthread_start == (clock_t)-1)
	{
		/* failed to get CPU ticks */
	}
	kthread_time = kthread_end - kthread_start;
	printf("[kthread] kthread CPU time was %f ", kthread_time);

}

