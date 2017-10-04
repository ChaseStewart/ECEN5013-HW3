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

#define INPUT_LEN     4096
#define CHAR_SPACE    32
#define CHAR_NEWLINE  10
#define CHAR_CR       13

static volatile int thread1_state = IS_RUNNING; 
static volatile int thread2_state = IS_RUNNING; 
static volatile int thread3_state = IS_RUNNING; 

static  pthread_cond_t usr1_cv;
static  pthread_cond_t usr2_cv;

static  pthread_mutex_t usr1_mutex;
static  pthread_mutex_t usr2_mutex;


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
		pthread_cond_signal(&usr1_cv);
		thread3_state = IS_STOPPED;
		pthread_cond_signal(&usr2_cv);
	}
	else if (my_signal == SIGUSR1)
	{
		printf("\n[multithread_io] USR1 was sent!\n");
		signal(SIGUSR1, sig_handler);
		pthread_cond_signal(&usr1_cv);
	}
	else if (my_signal == SIGUSR2)
	{
		printf("\n[multithread_io] USR2 was sent!\n");
		signal(SIGUSR2, sig_handler);
		pthread_cond_signal(&usr2_cv);
		
	}
	else if (my_signal == SIGINT)
	{
		printf("\n[multithread_io] CTRL+C was pressed! Goodbye...\n");
		signal(SIGINT, sig_handler);
		thread1_state = IS_STOPPED;
		thread2_state = IS_STOPPED;
		pthread_cond_signal(&usr1_cv);
		thread3_state = IS_STOPPED;
		pthread_cond_signal(&usr2_cv);
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
	printf("[multithread_io][thread2] opened file %s\n", my_file_name);

	while(thread2_state == IS_RUNNING)
	{
		/* wait for signal */
		pthread_cond_wait(&usr1_cv, &usr1_mutex);
		if(thread2_state == IS_STOPPED)
		{
			printf("[multithread_io][thread2] thread 2 dead!\n");
			fclose(in_file);
			return NULL;
		}

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
		printf("[multithread_io][thread2] ***FILE STATS ***\n\tnum_chars: %d\tnum_words: %d\tnum_lines: %d\n\n", num_chars, num_words, num_lines);
	}
	return NULL;
}

void *thread_three_main(void *in_file_name)
{
	while(thread3_state == IS_RUNNING)
	{
		/* wait for signal */
		pthread_cond_wait(&usr2_cv, &usr2_mutex);
		printf("[multithread_io][thread3] Hello from thread 3!\n");
		
	}
	printf("[multithread_io][thread3] thread 3 dead!\n");
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

	pthread_cond_init(&usr1_cv, NULL);
	pthread_cond_init(&usr2_cv, NULL);
	
	pthread_mutex_init(&usr1_mutex, NULL);
	pthread_mutex_init(&usr2_mutex, NULL);

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
		printf("\n[multithread_io][thread1] ERROR: Failed to open file! Closing...\n");
		exit(1);
	}
	printf("[multithread_io][thread1] File %s opened\n", out_file_name);
	
	/* Initialize thread2 */
	if (pthread_create(&thread_two, NULL, thread_two_main, out_file_name) != 0)
	{
		printf("[multithread_io][thread1] Failed to create thread 2!\n");
		return 1;
	}
	
	/* initialize thread3 */
	if (pthread_create(&thread_three, NULL, thread_three_main, out_file_name) != 0)
	{
		printf("[multithread_io][thread1] Failed to create thread 3!\n");
		return 1;
	}
	
	/* Run the main thread0 process*/
	printf("\tPlease type input:\n");
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
		printf("[multithread_io][thread1] failed to reap thread 2\n");
		return 1;
	}
	
	/* on close, reap thread_three */
	if (pthread_join(thread_three, NULL) != 0)
	{
		printf("[multithread_io][thread1] failed to reap thread 3\n");
		return 1;
	}

	printf("[multithread_io][thread1] Sucessfully reaped all threads\n");
	return 0;
}
