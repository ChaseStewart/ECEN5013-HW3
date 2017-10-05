/*****************************************************
 * Redistribution, modification or use of this software in source or binary forms 
 * is permitted as long as the files maintain this copyright. Users are permitted to 
 * modify this and use it to learn about the field of embedded software but don't copy 
 * my (Chase E Stewart's) work for class, I worked really hard on this. Alex Fosdick and 
 * the University of Colorado and Chase E Stewart are not liable for any misuse of this material. 
 * License copyright (C) 2017 originally from Alex Fosdick, code by Chase E Stewart.
 *****************************************************/
/**
 * @file multithread_io.h
 * @brief header for the multithreaded file IO program
 *
 * 
 *
 * @author Chase E Stewart
 * @date October 5 2017
 * @version 1.1
 *
 */

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

/* misc variables */
#define INPUT_LEN     4096

/* char values */
#define CHAR_CR       13
#define CHAR_NEWLINE  10
#define CHAR_SPACE    32
#define ASCII_START   32
#define ASCII_STOP    126

/* set globals for thread states */
static volatile int thread1_state = IS_RUNNING; 
static volatile int thread2_state = IS_RUNNING; 
static volatile int thread3_state = IS_RUNNING; 

/* SIGUSR1 SIGUSR2 mutexes and condition variables */
static pthread_cond_t usr1_cv;
static pthread_cond_t usr2_cv;
static pthread_mutex_t usr1_mutex;
static pthread_mutex_t usr2_mutex;

/* Stats mutex */
static pthread_mutex_t global_mutex;

/* struct for tty stats */
struct tty_stats {
	int num_chars;
	int num_words;
	int num_lines;
};

/* struct to pass to thread */
struct my_thread_info {
	char *file_name;
	struct tty_stats stats;
};

/* command-line options */
static struct option options[] = {
	{"filename", required_argument, NULL, 'f'},
	{"help", no_argument, NULL, 'h'},
	{NULL, 0, 0, 0}
};



/* prototypes */

/*
 * @brief print out 'help' for the program
 *
 * @param void 
 *
 * @return void
 */
void my_print_help(void);

/*
 * @brief handle chosen signals for program, signal or kill threads as needed  
 *
 * @param int my_signal- this holds the signal that caused this handler
 *   valid signals can be SIGINT, SIGTERM, SIGUSR1, SIGUSR2
 *
 * @return void
 */
void sig_handler(int my_signal);

/*
 * @brief main() function of thread_two: count chars/words/lines in file and update global struct
 *
 * @param void *thread_two_struct: holds a filename and a pointer to the global struct
 * the filename is opened into a file_pointer for this thread to read, 
 * and the global ref is updated with the counts 
 *
 * @return void 
 */
void *thread_two_main(void *thread_two_struct);

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
void *thread_three_main(void *thread_three_struct);

/*
 * @brief create a circular buffer
 *
 *
 * @param int argc: number of arguments provided to main
 * @param char *argv[], a pointer to an array of input args- parsed for the filename
 *
 * @return an int status
 */
int main(int argc, char *argv[]);





