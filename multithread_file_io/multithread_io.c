#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <getopt.h>
#include <signal.h>

#define IS_RUNNING 0
#define IS_STOPPED 1
#define INPUT_LEN 4096
#define CHAR_SPACE 32
#define CHAR_NEWLINE 10

static volatile int thread0_state = IS_RUNNING; 
static volatile int thread1_state = IS_RUNNING; 
static volatile int thread2_state = IS_RUNNING; 

void ctrlcHandler(int my_signal)
{
	if (my_signal == SIGINT)
	{
		signal(SIGINT, ctrlcHandler);
		thread0_state = IS_STOPPED;
	}
}


void my_print_help(void)
{
	printf("Usage: multithreadIO [-f] filename [-h]\n");
}

static struct option options[] = {
	{"filename", required_argument, NULL, 'f'},
	{"help", no_argument, NULL, 'h'},
	{NULL, 0, 0, 0}
};

void thread_two_main(void *in_file_name)
{
	int num_chars, num_words, num_lines;
	char *my_file_name;
	char c; 
	FILE *in_file;

	my_file_name = (char *)in_file_name;
	in_file = fopen(my_file_name, "r");
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
}

void thread_three_main(void *in_file_name)
{
	return;
}

int main(int argc, char *argv[])
{
	int  curr_arg;
	char out_file_name[INPUT_LEN];
	char input_char;
	FILE *out_file;
	
	out_file = NULL;
	signal(SIGINT, ctrlcHandler);

	curr_arg = 0;
	if (argc == 1)
	{
		my_print_help();
		return 0;
	}

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

	/* Initialize the processing thread */
	printf("[multithread_io] Filename is %s\n", out_file_name);

	
	printf("[multithread_io] File %s opened: Please type input:\n\n", out_file_name);

	while (thread0_state == IS_RUNNING)
	{
		input_char = getchar();
		putchar(input_char);
		out_file = fopen(out_file_name, "a");
		if (out_file == NULL)
		{
			printf("\nERROR: Failed to open file! Closing...\n");
			exit(1);
		}
		if (input_char >= 0)
		{
			fputc(input_char,out_file);
		}
		fclose(out_file);
	}
	printf("[multithread_io] CTRL+C was pressed! Goodbye...\n");
	return 0;
}

