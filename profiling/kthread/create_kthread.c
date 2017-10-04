#include <linux/kthread.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/jiffies.h>

int kthread_function(void *data){
	printk("[profile_kthreads][child] Hello from child\n");
	do_exit(0);
}

int get_kthread_time(void){
	unsigned long kthread_start, kthread_end, kthread_time;
	struct task_struct *kthread_task;

	printk("[profile_kthreads] Initialize module\n");
	
	kthread_start = get_jiffies_64();	
	
	/* call kthread_create */
	kthread_task = kthread_create(kthread_function, NULL, "timed_kthread_example");
	if (IS_ERR(kthread_task))
	{
		printk("[profile_kthreads] Error creating kthread! Exiting module!\n");
		return 1;
	}
	wake_up_process(kthread_task);

	kthread_end = get_jiffies_64();	
	
	kthread_time = (kthread_end - kthread_start);
	printk("[profile_kthreads] kthread start %ld end %ld CPU time was %ld\n", kthread_start, kthread_end, kthread_time);
	return 0;
}

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
