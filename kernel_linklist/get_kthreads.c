#include <stdio.h>
#include <linux/sched.h>
#include <linux/kernel.h>
#include <linux/module.h>


int main(void)
{
	struct task_struct *my_linklist;
	/* For each process in linux processes, get the name, kthread_id, status,  num_children */

	/* get my pid via getpid*/

	/* get to this pid node by matching on pid */		
	for_each_process(my_linklist)
	{	
		/* if my_pid = getpid*/
		
		/* pull name, thread_id, status, then recursively grab children */ 
		printf("[%d] name:%s, status:%d, num_children:%d \n", thread_id, name, status, children);
	}


}


