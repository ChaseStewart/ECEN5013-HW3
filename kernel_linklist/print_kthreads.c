/*****************************************************
 * Redistribution, modification or use of this software in source or binary forms 
 * is permitted as long as the files maintain this copyright. Users are permitted to 
 * modify this and use it to learn about the field of embedded software but don't copy 
 * my (Chase E Stewart's) work for class, I worked really hard on this. Alex Fosdick and 
 * the University of Colorado and Chase E Stewart are not liable for any misuse of this material. 
 * License copyright (C) 2017 originally from Alex Fosdick, code by Chase E Stewart.
 *****************************************************/
/**
 * @file print_kthreads.c
 * @brief A kernel module to get all kthreads 
 * 
 * When this module is loaded, it iterates through
 * the linklist of kernel tasks up to the init process 
 * and prints formatted stats to stdout
 * 
 * @author Chase E Stewart
 * @date October 5 2017
 * @version 1.1
 *
 */
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched/signal.h>
#include <linux/init.h>
#include <linux/slab.h>


/*
 * @brief iterate from current task_struct to init  
 * printing stats from the struct along the way
 *
 * @param void 
 *
 * @return int- return status of the function 
 */
int print_kernel_threads(void)
{
	struct task_struct *my_taskstruct;
	int my_task_state, my_num_children;
	struct list_head *current_node;
	pid_t my_pid;
	char *my_task_name;

	/* allocate char array for task_struct->comm field */
	printk("[print_kthread_ids] Initializing module!\n");
	my_task_name = (char *)kmalloc(2048*sizeof(char), GFP_KERNEL);

	/* For each process in linux processes, get name, pid, status, num_children */
	for(my_taskstruct = current; my_taskstruct != &init_task; my_taskstruct = my_taskstruct->parent)	
	{
		/* get args from the task_struct*/
		my_task_state = my_taskstruct->state;
		my_pid        = my_taskstruct->pid;
		sprintf(my_task_name, my_taskstruct->comm);
		my_num_children = 0;

		/* use macro to get num children*/
		list_for_each(current_node, &my_taskstruct->children)
		{
			my_num_children++;
		}

		/* pull name, thread_id, status, then recursively grab children */ 
		printk("[print_kthread_ids][%d] name:%s, status:%d, num_children:%d \n", \
								my_pid,        \
								my_task_name,  \
								my_task_state, \
								my_num_children);
	}
	printk("[print_kthread_ids] End of list!\n");
	
	kfree(my_task_name);
	return 0;
}

/*
 * @brief exit the module and print that exit occurred  
 *
 * @param void 
 *
 * @return void
 */
static void my_module_exit(void)
{
	printk("[print_kthread_ids] Exiting module!\n");
	return;
}


/* set the init and exit function using a macro */
module_init(print_kernel_threads);
module_exit(my_module_exit);

/* Set module parameters */
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("ECEN5013 HW3 print kernel_ids and info");
MODULE_AUTHOR("Chase E Stewart");
