#include <time.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define IS_CHILD 0
#define FORK_SUCCEEDED 0

int main(void){

	
	pid_t my_pid;
	clock_t my_start, my_end;
	double my_time;


	/* capture fork_start time */
	my_start=clock();
	if (my_start == (clock_t)-1)
	{
		/* failed to get CPU ticks */
		printf("[profile-fork-exec] failed to get fork_start time\n");
	}
	/* call fork */
	my_pid = fork();
	
	/* if fork fails, return an error*/
	if (my_pid < FORK_SUCCEEDED)
	{
		printf("[profile-fork-exec] failed to fork\n");
		return((int) my_pid);
	}
	else
	{
		
		if (my_pid == IS_CHILD)
		{
			printf("[profile-fork-exec][child] running \"ls\"\n");
			execlp("/bin/ls", "ls", NULL);
		}
		else
		{
			printf("[profile-fork-exec][parent] waiting for child\n");
			wait(NULL);
		
			/* capture exec_end time */
			my_end = clock();
			printf("[profile-fork-exec][parent] stop clock\n");
			if (my_end == (clock_t)-1)
			{
				/* failed to get CPU ticks */
				printf("[profile-fork-exec] failed to get fork_start time\n");
			}
			my_time = my_end - my_start;
			printf("[profile-fork-exec] fork CPU time was %f\n", my_time);
		}
		return 0;
	}
}

