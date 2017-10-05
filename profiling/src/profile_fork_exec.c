/*****************************************************
 * Redistribution, modification or use of this software in source or binary forms 
 * is permitted as long as the files maintain this copyright. Users are permitted to 
 * modify this and use it to learn about the field of embedded software but don't copy 
 * my (Chase E Stewart's) work for class, I worked really hard on this. Alex Fosdick and 
 * the University of Colorado and Chase E Stewart are not liable for any misuse of this material. 
 * License copyright (C) 2017 originally from Alex Fosdick, code by Chase E Stewart.
 *****************************************************/
/**
 * @file profile_fork_exec.c
 * @brief A short program to profile a new child created via fork() then exec()
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
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/* return status values */
#define IS_CHILD 0
#define FORK_SUCCEEDED 0

/*
 * @brief catch clock start time, then call fork() and exec() to do an ls 
 * have parent process wait() on child to terminate after ls, then stop clock
 * return the delta time to stdout 
 *
 * @param void 
 *
 * @return int- return status of the function 
 */
int main(void){

	
	pid_t my_pid;
	clock_t my_start, my_end;
	long int my_time;

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
		/* have child process use execlp to call "ls" */		
		if (my_pid == IS_CHILD)
		{
			printf("[profile-fork-exec][child] running \"ls\"\n");
			execlp("/bin/ls", "ls", NULL);
		}

		/* have parent process wait for child, then stop the clock and print results */		
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

			/*calculate and print delta time */
			my_time = my_end - my_start;
			printf("[profile-fork-exec] fork CPU time was %ld\n", my_time);
		}
		return 0;
	}
}

