#include <time.h>
#include <stdint.h>
#include <stdio.h>

clock_t forkstart, forkend, execstart, execend;
double fork_time, exec_time;



int main(void){
	forkstart=clock();
	if (forkstart == (clock_t)-1)
	{
		/* failed to get CPU ticks */
	}
	/* call fork */
	forkend=clock();
	if (forkstart == (clock_t)-1)
	{
		/* failed to get CPU ticks */
	}
	fork_time = forkend - forkstart;
	printf("[fork] fork CPU time was %f ", fork_time);


	execstart=clock();
	if (forkstart == (clock_t)-1)
	{
		/* failed to get CPU ticks */
	}
	/* call exec */
	execend=clock();
	if (forkstart == (clock_t)-1)
	{
		/* failed to get CPU ticks */
	}
	exec_time = execend - execstart;
	printf("[exec] exec CPU time was %f ", exec_time);
}

