/*****************************************************
 * Redistribution, modification or use of this software in source or binary forms 
 * is permitted as long as the files maintain this copyright. Users are permitted to 
 * modify this and use it to learn about the field of embedded software but don't copy 
 * my (Chase E Stewart's) work for class, I worked really hard on this. Alex Fosdick and 
 * the University of Colorado and Chase E Stewart are not liable for any misuse of this material. 
 * License copyright (C) 2017 originally from Alex Fosdick, code by Chase E Stewart.
 *****************************************************/
/**
 * @file multithread_io.c
 * @brief source code for the multithreaded file IO program
 *
* 
 *
 * @author Chase E Stewart
 * @date October 5 2017
 * @version 1.1
 *
 */

#include "multithread_io.h"



/* SIGUSR1 SIGUSR2 mutexes and condition variables */
static volatile struct tty_stats *my_stats;

/*
 * @brief handle chosen signals for program, signal or kill threads as needed  
 *
 * @param int my_signal- this holds the signal that caused this handler
 *   valid signals can be SIGINT, SIGTERM, SIGUSR1, SIGUSR2
 *
 * @return void
 */
void sig_handler(int my_signal)
{
	/* For SIGTERM, stop all threads gracefully */
	if (my_signal == SIGTERM)
	{
		printf("\n[multithread_io] pkill was sent!\n");
		signal(SIGTERM, sig_handler);
		thread1_state = IS_STOPPED;
		thread2_state = IS_STOPPED;
		pthread_cond_signal(&usr1_cv);
		thread3_state = IS_STOPPED;
		pthread_cond_signal(&usr2_cv);
	}
	/* For SIGUSR1, have thread_two count stats */
	else if (my_signal == SIGUSR1)
	{
		printf("\n[multithread_io] USR1 was sent!\n");
		signal(SIGUSR1, sig_handler);
		pthread_cond_signal(&usr1_cv);
	}
	/* For SIGUSR2, have thread_three count stats */
	else if (my_signal == SIGUSR2)
	{
		printf("\n[multithread_io] USR2 was sent!\n");
		signal(SIGUSR2, sig_handler);
		pthread_cond_signal(&usr2_cv);
		
	}
	
	/* For SIGINT, stop all threads gracefully */
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

/*
 * @brief print out 'help' for the program
 *
 * @param void 
 *
 * @return void
 */
void my_print_help(void)
{
	printf("Usage: multithreadIO [-f] filename [-h]\n");
}


/*
 * @brief main() function of thread_two: count chars/words/lines in file and update global struct
 *
 * @param void *thread_two_struct: holds a filename and a pointer to the global struct
 * the filename is opened into a file_pointer for this thread to read, 
 * and the global ref is updated with the counts 
 *
 * @return void 
 */
void *thread_two_main(void *thread_two_struct)
{
	int local_chars, local_words, local_lines;
	struct my_thread_info *data_struct;
	struct tty_stats *thread_two_stats;
	char *my_file_name;
	FILE *in_file;
	char c, lastchar; 
	char *word;
	static ENTRY *search_tab;
	static ENTRY *enter_tab;
	unsigned long temp;
	
	

	search_tab = (ENTRY *)malloc(sizeof(ENTRY));
	enter_tab = (ENTRY *)malloc(sizeof(ENTRY));

	data_struct = (struct my_thread_info *)thread_two_struct;
	my_file_name = data_struct->file_name;
	thread_two_stats = &data_struct->stats;

	word = (char *)malloc(sizeof(char) * MAX_WORD);

	/* Loop until this state is set to IS_STOPPED by sigint_handler */
	while(thread2_state == IS_RUNNING)
	{
		/* wait for USR1 signal from sigint_handler */
		pthread_cond_wait(&usr1_cv, &usr1_mutex);
		
		/* don't run the last time if stopped  */
		if(thread2_state == IS_STOPPED)
		{
			printf("[multithread_io][thread2] thread 2 dead!\n");
			return NULL;
		}

		/* re-init counts to 0 for each USR1 signal */
		local_chars = 0;
		local_words = 0;
		local_lines = 0;

		in_file = fopen(my_file_name, "r");
		printf("[multithread_io][thread2] opened file %s\n", my_file_name);
		fseek(in_file, 0, SEEK_SET);

		lastchar = 0;
		c = 34;
		/* read the whole file, increment vars  */
		while(c != EOF)
		{
			c = fgetc(in_file);
			if (c == EOF)
			{
				break;
			}
			local_chars++;
			
			/* try to actually get words, not just spaces */
			if ((c == CHAR_SPACE) && ( (lastchar != CHAR_SPACE) || (lastchar != CHAR_NEWLINE)))
			{
				local_words++;
			}
			else if (c == CHAR_NEWLINE)
			{
				local_lines++;
			}

			pthread_mutex_lock(&global_mutex);
			thread_two_stats->num_chars = local_chars;
			thread_two_stats->num_words = local_words;
			thread_two_stats->num_lines = local_lines;
			pthread_mutex_unlock(&global_mutex);
			lastchar = c;
		}
		
		fseek(in_file, 0, SEEK_SET);
		hcreate(4096);

		while(fscanf(in_file, "%2048s", word) == 1) /* MAX_WORD = 2048 */ 
		{
			search_tab->data = 0;
			search_tab->key = word;
			enter_tab = hsearch(*search_tab, FIND);
			if(enter_tab == NULL)
			{
				enter_tab = hsearch(*search_tab, ENTER);
			}
			else
			{
				enter_tab->data = (unsigned long * )enter_tab->data +1;
				temp = (unsigned long) enter_tab->data/8;
				hsearch(*enter_tab, ENTER);
			}
		}

		hdestroy();
		fclose(in_file);
	}
	/* Should never get here, but clean up anyways  */
	printf("[multithread_io][thread2] thread 2 dead- should never get here!\n");
	return NULL;
}

/*
 * @brief main() function of thread_three: read global struct and print results to stdout 
 *
 *
 * @param void *thread_three_struct: same as thread_two_struct, holds a filename 
 * and a pointer to the global struct. The filename is ignored, 
 * and the global ref is updated with the counts 
 *
 * @return circ_buff_status - enum of status
 */
void *thread_three_main(void *thread_three_struct)
{
	int local_chars, local_words, local_lines;
	struct my_thread_info *data_struct;
	struct tty_stats *thread_three_stats;
	
	data_struct = (struct my_thread_info *)thread_three_struct;
	thread_three_stats = &data_struct->stats;

	while(thread3_state == IS_RUNNING)
	{
		/* wait for signal */
		pthread_cond_wait(&usr2_cv, &usr2_mutex);

		/* don't run the last time if stopped  */
		if(thread3_state == IS_STOPPED)
		{
			printf("[multithread_io][thread3] thread 3 dead!\n");
			return NULL;
		}

		
		/* protect changes to global struct via mutex lock+unlock */
		pthread_mutex_lock(&global_mutex);
		local_chars = thread_three_stats->num_chars;
		local_words = thread_three_stats->num_words;
		local_lines = thread_three_stats->num_lines;
		pthread_mutex_unlock(&global_mutex);

		/* now print results */		
		printf("[multithread_io][thread3] ***FILE STATS ***\n\tnum_chars: %d\tnum_words: %d\tnum_lines: %d\n\n", local_chars, local_words, local_lines);
		
	}

	/* you really should never get here*/
	printf("[multithread_io][thread3] thread 3 dead- should not get here!\n");
	return NULL;
}

/*
 * @brief create a circular buffer
 *
 *
 * @param int argc: number of arguments provided to main
 * @param char *argv[], a pointer to an array of input args- parsed for the filename
 *
 * @return an int status
 */
int main(int argc, char *argv[])
{
	int  curr_arg;
	char out_file_name[INPUT_LEN];
	char input_char;
	FILE *out_file;
	pthread_t thread_two, thread_three;
	struct my_thread_info *thread_info;

	/* hijack all signals to this handler */
	signal(SIGINT,  sig_handler);
	signal(SIGUSR1, sig_handler);
	signal(SIGUSR2, sig_handler);
	signal(SIGTERM, sig_handler);

	/* instantiate SIGUSR cond/mutex */
	pthread_cond_init(&usr1_cv, NULL);
	pthread_cond_init(&usr2_cv, NULL);
	pthread_mutex_init(&usr1_mutex, NULL);
	pthread_mutex_init(&usr2_mutex, NULL);

	/* init the global  */
	pthread_mutex_init(&global_mutex, NULL);

	out_file = NULL;

	/* allocate tty_stats struct */
	my_stats = (struct tty_stats *)malloc(sizeof(struct tty_stats));
	my_stats->num_chars =0;
	my_stats->num_words =0;
	my_stats->num_lines =0;
	
	/* if no args provided, print help and exit */
	if (argc == 1)
	{
		my_print_help();
		return 0;
	}

	/* now iterate through all args, switching on arg char */
	curr_arg = 0;
	while (curr_arg >= 0)
	{
		/* FYI options struct is in multithread_io.h */
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


	/* instantiate the thread_info struct */	
	thread_info = (struct my_thread_info *)malloc(sizeof(struct my_thread_info));
	thread_info->file_name  = out_file_name;
	thread_info->stats = *my_stats;

	/* Initialize thread2 */	
	if (pthread_create(&thread_two, NULL, thread_two_main, thread_info) != 0)
	{
		printf("[multithread_io][thread1] Failed to create thread 2!\n");
		return 1;
	}
	
	/* initialize thread3 */
	if (pthread_create(&thread_three, NULL, thread_three_main, thread_info) != 0)
	{
		printf("[multithread_io][thread1] Failed to create thread 3!\n");
		return 1;
	}
	
	/* Run the main thread0 process */
	printf("\tPlease type input- only chars %d-%d are counted for char:\n", ASCII_START, ASCII_STOP);
	while (thread1_state == IS_RUNNING)
	{
		/* get some chars, put them out to screen, if chars are valid, write them to file */
		input_char = getchar();
		putchar(input_char);
	
		out_file = fopen(out_file_name, "a");

		if ((input_char >= ASCII_START) && (input_char <= ASCII_STOP))
		{
			fputc(input_char,out_file);
		}
		else if ((input_char == CHAR_CR) || (input_char == CHAR_NEWLINE))
		{
			fputc(input_char, out_file);
		}
		fclose(out_file);
	}

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

	/* now exit once all are reaped */
	printf("[multithread_io][thread1] Sucessfully reaped all threads\n");
	
	/* destroy from   */
	pthread_cond_destroy(&usr1_cv);
	pthread_cond_destroy(&usr2_cv);
	pthread_mutex_destroy(&usr1_mutex);
	pthread_mutex_destroy(&usr2_mutex);
	pthread_mutex_destroy(&global_mutex);
	free(thread_info);
	printf("[multithread_io][thread1] Freed all global resources\n");
	printf("[multithread_io][thread1] Goodbye!\n");

	return 0;
}

