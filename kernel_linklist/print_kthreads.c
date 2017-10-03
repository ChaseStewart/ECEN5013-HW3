#include <stdio.h>
#include <linux/sched.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>


int print_kernel_threads(void)
{
	struct task_struct *my_linklist;
	int my_task_state, my_num_children;
	char my_task_name[1000];
	pid_t my_pid;
	
	printf("[print_kthread_ids] Starting module!\n")

	/* For each process in linux processes, get name, pid, status, num_children */
	for_each_process(my_linklist)
	{	
		/* if my_pid = getpid*/
		my_task_state = my_linklist->state;
		my_thread_id  = my_linklist->pid;
		my_task_name  = my_linklist->comm;
	
		/* pull name, thread_id, status, then recursively grab children */ 
		printf("[print_kthread_ids][%d] name:%s, status:%d, num_children:%d \n", 
								my_thread_id,  \
								my_task_name,  \
								my_task_state, \
								my_num_children);
	}
}

static void my_module_exit(void)
{
	printf("[print_kthread_ids] Exiting module!\n")
}


/* set the init and exit function using a macro */
module_init(print_kernel_threads);
module_exit(my_module_exit);

/* Set module parameters */
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("ECEN5013 HW3 print kernel_ids and info");
MODULE_AUTHOR("Chase E Stewart");
