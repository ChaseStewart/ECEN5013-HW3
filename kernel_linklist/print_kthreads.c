#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched/signal.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/plist.h>

int print_kernel_threads(void)
{
	struct task_struct *my_taskstruct;
	int my_task_state, my_num_children;
	pid_t my_pid;
	char *my_task_name;
	
	struct list_head *current_node;

	printk("[print_kthread_ids] Starting module!\n");
	my_task_name = (char *)kmalloc(2048*sizeof(char), GFP_KERNEL);

	/* For each process in linux processes, get name, pid, status, num_children */
	for_each_process(my_taskstruct){	
		/* get args from the task_struct*/
		my_task_state = my_taskstruct->state;
		my_pid        = my_taskstruct->pid;
		sprintf(my_task_name, my_taskstruct->comm);
		my_num_children = 0;

		/* get num children*/
		current_node = &(my_taskstruct->children);
		while(current_node != NULL)
		{
			current_node = current_node->next;
			my_num_children++;
			printk("found child!\n");
		}


		/* pull name, thread_id, status, then recursively grab children */ 
		printk("[print_kthread_ids][%d] name:%s, status:%d, num_children:%d \n", 
								my_pid,        \
								my_task_name,  \
								my_task_state, \
								my_num_children);
	}
	return 0;
}

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
