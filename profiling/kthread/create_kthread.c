#include <linux/kthread.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/time.h>

/*
 * struct kthread_create_info
 * {
 * 	/ Information passed to kthread() from kthreadd. /
 * 	int (*threadfn)(void *data);
 * 	void *data;
 * 	int node;
 * 
 * 	/ Result passed back to kthread_create() from kthreadd. /
 * 	struct task_struct *result;
 * 	struct completion *done;
 * 
 * 	struct list_head list;
 * };
 * 
 * struct kthread {
 * 	unsigned long flags;
 * 	unsigned int cpu;
 * 	void *data;
 * 	struct completion parked;
 * 	struct completion exited;
 * };
 * 
 */

int get_kthread_time(void){
	clock_t kthread_start, kthread_end;
	double kthread_time;
	struct task_struct *kthread_task;

	printk("[profile_kthreads] Initialize module\n");
	kthread_start=clock();
	if (kthread_start == (clock_t)-1)
	{
		/* failed to get CPU ticks */
		printk("[profile_kthreads] Failed to get start time\n");
	}
	/* call kthread_create */
	kthread_end=clock();
	if (kthread_start == (clock_t)-1)
	{
		/* failed to get CPU ticks */
		printk("[profile_kthreads] Failed to get end time\n");
	}
	kthread_time = kthread_end - kthread_start;
	printk("[profile_kthreads] kthread CPU time was %f\n", kthread_time);
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
