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
#define ASCII_STOP    127

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


void my_print_help(void);

void sig_handler(int my_signal);

void *thread_two_main(void *in_file_name);

void *thread_three_main(void *in_file_name);

int main(int argc, char *argv[]);





