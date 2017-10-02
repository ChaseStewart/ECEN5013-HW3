#include <stdio.h>
#include <linux/sched.h>
#include <linux/kernel.h>
#include <linux/module.h>


int main(void)
{
	struct task_struct *my_linklist;
	for_each_process(my_linklist)
	{	
		
		printf("[]")	
	}


}


