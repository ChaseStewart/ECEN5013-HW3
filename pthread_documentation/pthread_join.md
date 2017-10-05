# Join
Sleep until a pthread terminates, then join with it and get its retval via a pointer.

```
extern int pthread_join (pthread_t __th, void **__thread_return);
```

## Parameters
* pthread_t __th: the pthread that the caller wishes to join with. Once "thread" terminates, it will be guaranteedly terminated 
* void **__thread_return: after concluding the join, "retval" will hold whatever was returned by "thread" when it called pthread_exit.

## Description
Once this function is called, the calling function will wait until thread __th terminates via a signal, exit, cancel, etc. When __th exits, it will give its return status to the caller of pthread_join via __thread_return.


## Outputs
* int: pthread_join outputs its status via an int- a success is denoted by 0, while other errors can be determined by a nonzero error_number. 

## Notes 
To sucessfully run pthread_join, a few main things need to happen: pthread "thread" must already have been created via pthread_create and must currently exist. This is the clean way to reap a thread- no matter if a pthread exists for a short time or the duration of a program, one should do this to one's created pthreads.

