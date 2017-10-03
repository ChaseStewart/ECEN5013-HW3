#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <getopt.h>
#include <signal.h>

/* state variables */
#define IS_RUNNING    0
#define IS_STOPPED    1
#define THREAD1_PRINT 2
#define THREAD2_PRINT 3

#define INPUT_LEN     4096
#define CHAR_SPACE    32
#define CHAR_NEWLINE  10
#define CHAR_CR       13

static volatile int thread1_state = IS_RUNNING; 
static volatile int thread2_state = IS_RUNNING; 
static volatile int thread3_state = IS_RUNNING; 

static struct option options[] = {
	{"filename", required_argument, NULL, 'f'},
	{"help", no_argument, NULL, 'h'},
	{NULL, 0, 0, 0}
};

void sig_handler(int my_signal)
{
	if (my_signal == SIGTERM)
	{
		printf("\n[multithread_io] pkill was sent! Goodbye...\n");
		signal(SIGTERM, sig_handler);
		thread1_state = IS_STOPPED;
		thread2_state = IS_STOPPED;
		thread3_state = IS_STOPPED;
	}
	else if (my_signal == SIGUSR1)
	{
		printf("\n[multithread_io] USR1 was sent!\n");
		signal(SIGUSR1, sig_handler);
		/* TODO signal this guy to run*/
		thread2_state = THREAD1_PRINT;
	}
	else if (my_signal == SIGUSR2)
	{
		printf("\n[multithread_io] USR2 was sent!\n");
		signal(SIGUSR2, sig_handler);
		thread2_state = THREAD2_PRINT;
	}
	else if (my_signal == SIGINT)
	{
		printf("\n[multithread_io] CTRL+C was pressed! Goodbye...\n");
		signal(SIGINT, sig_handler);
		thread1_state = IS_STOPPED;
		thread2_state = IS_STOPPED;
		thread3_state = IS_STOPPED;
	}
}


void my_print_help(void)
{
	printf("Usage: multithreadIO [-f] filename [-h]\n");
}

void *thread_two_main(void *in_file_name)
{
	int num_chars, num_words, num_lines;
	char *my_file_name;
	char c; 
	FILE *in_file;

	my_file_name = (char *)in_file_name;
	in_file = fopen(my_file_name, "r");
	printf("[thread2] opened file %s\n", my_file_name);
	while(c != EOF)
	{
		c = fgetc(in_file);
		num_chars++;
		if (c == CHAR_SPACE)
		{
			num_words++;
		}
		else if (c == CHAR_NEWLINE)
		{
			num_lines++;
		}
	}
	printf("[thread2] num_chars: %d\tnum_words: %d\tnum_lines: %d\n", num_chars, num_words, num_lines);
	printf("[thread2] thread 2 dead!\n");
	fclose(in_file);
	return NULL;
}

void *thread_three_main(void *in_file_name)
{
	printf("thread 3 dead!\n");
	return NULL;
}

int main(int argc, char *argv[])
{
	int  curr_arg;
	char out_file_name[INPUT_LEN];
	char input_char;
	FILE *out_file;
	pthread_t thread_two, thread_three;

	/* hijack all signals to this handler */	
	signal(SIGINT,  sig_handler);
	signal(SIGUSR1, sig_handler);
	signal(SIGUSR2, sig_handler);
	signal(SIGTERM, sig_handler);
	
	out_file = NULL;

	/* parse args */
	if (argc == 1)
	{
		my_print_help();
		return 0;
	}

	curr_arg = 0;
	while (curr_arg >= 0)
	{
		curr_arg = getopt_long(argc, argv, "f:h", options, NULL);
		if (curr_arg < 0 )
		{
			continue;
		}
		switch (curr_arg)
		{
			/* get filename*/
			case 'f':
				/*  get the actual arg */
				strcpy(out_file_name, optarg);
				break;

			/* print out the help*/
			case 'h':
			default:
				my_print_help();
				return 0;
		}
	}

	/* open the file for writing */
	out_file = fopen(out_file_name, "a");
	if (out_file == NULL)
	{
		printf("\nERROR: Failed to open file! Closing...\n");
		exit(1);
	}
	printf("[multithread_io] File %s opened\n", out_file_name);
	
	/* Initialize thread2 */
	if (pthread_create(&thread_two, NULL, thread_two_main, out_file_name) != 0)
	{
		printf("Failed to create thread 2!\n");
		return 1;
	}
	
	/* initialize thread3 */
	if (pthread_create(&thread_three, NULL, thread_three_main, out_file_name) != 0)
	{
		printf("Failed to create thread 3!\n");
		return 1;
	}
	
	/* Run the main thread0 process*/
	printf("Please type input:\n");
	while (thread1_state == IS_RUNNING)
	{
		input_char = getchar();
		putchar(input_char);

		if (input_char > 0)
		{
			fputc(input_char,out_file);
		}
	}

	fclose(out_file);

	/* on close, reap thread_two */
	if (pthread_join(thread_two, NULL) != 0)
	{
		printf("failed to reap thread 2\n");
		return 1;
	}
	
	/* on close, reap thread_three */
	if (pthread_join(thread_three, NULL) != 0)
	{
		printf("failed to reap thread 3\n");
		return 1;
	}

	printf("Sucessfully reaped all threads\n");
	return 0;
}
