#include "multithread_io.h"

/* SIGUSR1 SIGUSR2 mutexes and condition variables */
static volatile struct tty_stats *my_stats;

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


void my_print_help(void)
{
	printf("Usage: multithreadIO [-f] filename [-h]\n");
}


void *thread_two_main(void *thread_two_struct)
{
	struct my_thread_info *data_struct;
	struct tty_stats *thread_two_stats;
	char *my_file_name;
	FILE *in_file;
	char c; 

	data_struct = (struct my_thread_info *)thread_two_struct;
	my_file_name = data_struct->file_name;
	thread_two_stats = &data_struct->stats;


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

		in_file = fopen(my_file_name, "r");
		printf("[multithread_io][thread2] opened file %s\n", my_file_name);
		fseek(in_file, 0, SEEK_SET);

		c = 34;
		/* read the whole file, increment vars  */
		while(c != EOF)
		{
			c = fgetc(in_file);
			pthread_mutex_lock(&global_mutex);
			thread_two_stats->num_chars++;
			if (c == CHAR_SPACE)
			{
				/* TODO fixme get real words not just spaces */
				thread_two_stats->num_words++;
			}
			else if (c == CHAR_NEWLINE)
			{
				thread_two_stats->num_lines++;
			}
			pthread_mutex_unlock(&global_mutex);
		}
		fclose(in_file);
	}
	/* Should never get here, but clean up anyways  */
	printf("[multithread_io][thread2] thread 2 dead- should never get here!\n");
	//fclose(in_file);
	return NULL;
}

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

		
		pthread_mutex_lock(&global_mutex);
		local_chars = thread_three_stats->num_chars;
		local_words = thread_three_stats->num_words;
		local_lines = thread_three_stats->num_lines;
		pthread_mutex_unlock(&global_mutex);
		
		printf("[multithread_io][thread3] ***FILE STATS ***\n\tnum_chars: %d\tnum_words: %d\tnum_lines: %d\n\n", local_chars, local_words, local_lines);
		
	}

	/* you really should never get here*/
	printf("[multithread_io][thread3] thread 3 dead- should not get here!\n");
	return NULL;
}

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
	//out_file = fopen(out_file_name, "a");
	//if (out_file == NULL)
	//{
	//	printf("\n[multithread_io][thread1] ERROR: Failed to open file! Closing...\n");
	//	exit(1);
	//}
	//printf("[multithread_io][thread1] File %s opened\n", out_file_name);
	
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
	
	/* Run the main thread0 process*/
	printf("\tPlease type input:\n");
	while (thread1_state == IS_RUNNING)
	{
		input_char = getchar();
		putchar(input_char);
	
		out_file = fopen(out_file_name, "a");

		if (input_char > 0)
		{
			fputc(input_char,out_file);
		}
		fclose(out_file);
	}
	//fclose(out_file);

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
