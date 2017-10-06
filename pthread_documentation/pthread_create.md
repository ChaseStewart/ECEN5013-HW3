# pthread_create
create a pthread and return its handle.

```
extern int pthread_create (pthread_t *__restrict __newthread,
			   const pthread_attr_t *__restrict __attr,
			   void *(*__start_routine) (void *),
			   void *__restrict __arg) __THROWNL __nonnull ((1, 3));
```

## Parameters
* pthread_t *__restrict __newthread: this will store a handle to the new pthread 
* const pthread_attr_t *__restrict __attr: A set of flags of type pthread_attr_t struct to be used in pthread creation 
* void *(__start_routine) : the routine that the new pthread will run upon creation. If the pthread needs args for __start_routine, it must get them from the 'args' parameter below
* void *__restrict __arg : a void pointer to any and all args needed by the '__start_routine' function

## Description
This creates and starts a new pthread within the process that called this function. The newly-created thread immediately begins to execute its provided function __start_routine, also using the args provided in __arg.

## Outputs
* extern int: pthread_create outputs its status via an int- a success is denoted by 0, while other errors can be determined by a nonzero error_number. 

## Notes 
To run pthread_create, a few main things need to happen: Function Fn (which the thread will execute) must be created and the desired set of input vars must also be instantiated. The task_struct pointer for the output must also be created if it does not already exist, Finally, all of these must be passed into the function.

## Example Code
Please see examples/pthread_example.c 

