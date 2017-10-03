#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched/signal.h>
#include <linux/init.h>
#include <linux/slab.h>
//#include <linux/plist.h>

int print_kernel_threads(void)
{
	struct task_struct *my_taskstruct;
	int my_task_state, my_num_children;
	struct list_head *current_node;
	pid_t my_pid;
	char *my_task_name;

	printk("[print_kthread_ids] Initializing module!\n");
	my_task_name = (char *)kmalloc(2048*sizeof(char), GFP_KERNEL);

	/* For each process in linux processes, get name, pid, status, num_children */
	for_each_process(my_taskstruct){	
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
