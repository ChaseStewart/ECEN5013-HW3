/*****************************************************
 * Redistribution, modification or use of this software in source or binary forms 
 * is permitted as long as the files maintain this copyright. Users are permitted to 
 * modify this and use it to learn about the field of embedded software but don't copy 
 * my (Chase E Stewart's) work for class, I worked really hard on this. Alex Fosdick and 
 * the University of Colorado and Chase E Stewart are not liable for any misuse of this material. 
 * License copyright (C) 2017 originally from Alex Fosdick, code by Chase E Stewart.
 *****************************************************/
/**
 * @file profile_kthread.c
 * @brief A short program to profile a new child created via kthread_create()
 * 
 * this kernel module uses processor time via linux/jiffies.h via the get_jiffies_64() macro. 
 * 
 * @author Chase E Stewart
 * @date October 5 2017
 * @version 1.1
 *
 */
#include <linux/kthread.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/jiffies.h>



/*
 * @brief short task for kthread to do,  
 * have kthread print a message then die 
 *
 * @param void  *data - unused, but kthread_create passes in a void * 
 *
 * @return int- a return status for the kthread 
 */
int kthread_function(void *data){
	printk("[profile_kthreads][child] Hello from child\n");
	do_exit(0);
}


/*
 * @brief catch clock start time, then call kthread_create() and wake_up_process() 
 * to make a thread do kthread_function() then stop clock
 * return the delta time to stdout 
 *
 * @param void 
 *
 * @return int- return status of the function 
 */
int get_kthread_time(void){
	unsigned long kthread_start, kthread_end, kthread_time;
	struct task_struct *kthread_task;

	printk("[profile_kthreads] Initialize module\n");
	/* get start time */
	kthread_start = get_jiffies_64();	
	
	/* call kthread_create and wake_up_process */
	kthread_task = kthread_create(kthread_function, NULL, "timed_kthread_example");
	if (IS_ERR(kthread_task))
	{
		printk("[profile_kthreads] Error creating kthread! Exiting module!\n");
		return 1;
	}
	wake_up_process(kthread_task);

	/* get the end time, time diff, and print it*/
	kthread_end = get_jiffies_64();	
	kthread_time = (kthread_end - kthread_start);
	printk("[profile_kthreads] kthread start %ld end %ld CPU time was %ld\n", kthread_start, kthread_end, kthread_time);
	return 0;
}


/*
 * @brief print that module is exiting, then exit 
 *
 * @param void 
 *
 * @return void
 */
static void my_module_exit(void)
{
	printk("[profile_kthreads] Exiting module!\n");
	return;
}

/* set the init and exit function using a macro */
module_init(get_kthread_time);
module_exit(my_module_exit);

/* Set module parameters */
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("ECEN5013 HW3 profile kthread time");
MODULE_AUTHOR("Chase E Stewart");
