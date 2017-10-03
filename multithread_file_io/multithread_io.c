#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <getopt.h>

#define IS_RUNNING 0
#define IS_STOPPED 1
#define INPUT_LEN 4096
#define CHAR_SPACE 32
#define CHAR_NEWLINE 10

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
	int my_state, curr_arg;
	char out_file_name[4096];
	char input_char;
	FILE *out_file;

	my_state = IS_RUNNING;
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
	while (my_state == IS_RUNNING)
	{
		input_char = getchar();
		out_file = fopen(out_file_name, "w");
		fputc(input_char,out_file);
		fclose(out_file);
		putchar(input_char);
	}
}

