# Join
Sleep until a pthread terminates, then join with it and get its retval via a pointer.

`int pthread_join(pthread_t thread, void **retval);`

## Parameters
*pthread_t thread: the pthread that the caller wishes to join with. Once "thread" terminates, it will be guaranteedly terminated 

*void **retval: after concluding the join, "retval" will hold whatever was returned by "thread" when it called pthread_exit.

## Description
This ##TODO TODO FIXME


## Outputs
*int: pthread_join outputs its status via an int- a success is denoted by 0, while other errors can be determined by a nonzero error_number. 

## How to Run
To sucessfully run pthread_join, a few main things need to happen: pthread "thread" must already have been created via pthread_create and must currently exist.  

