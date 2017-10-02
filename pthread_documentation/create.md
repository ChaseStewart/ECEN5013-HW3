# Create
create a pthread and return its handle.

`struct int pthread_create(int (*fn)(void *data), void *data, const char namefmt[], ... );`

## Parameters
*Fn: a pointer to the function this thread should execute

*data: a set of parameters passed into function Fn 

*namefmt: the name of the process

## Description
This creates and starts a new pthread within the process that called this function. The newly-created thread immediately begins to execute its provided function, also using the args provided in data

## Outputs
*int: pthread_create outputs its status via an int- a success is denoted by 0, while other errors can be determined by a nonzero error_number. 

## How to Run
To run pthread_create, a few main things need to happen: Function Fn (which the thread will execute) must be created and the desired set of input vars must also be instantiated. The task_struct pointer for the output must also be created if it does not already exist, Finally, all of these must be passed into the function.

