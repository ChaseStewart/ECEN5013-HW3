# Create
create a pthread and return its handle.

```
struct task_struct * kthread_create(int (*fn)(void *data), void *data, const char namefmt[], ... );
```

## Parameters
*Fn: a pointer to the function this thread should call
*data: a set of parameters passed into function Fn 
*namefmt: the name of the process

## Description
This creates a kthread that will use 

## Outputs
* task_struct *: kthread_create outputs a pointer to a 'task_struct' that holds information on the created thread.

## example code
To run kthread_create, a few main things need to happen: Function Fn (which the thread will execute) must be created and the desired set of input vars must also be instantiated. The task_struct pointer for the output must also be created if it does not already exist, Finally, all of these must be passed into the function.



