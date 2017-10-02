# pthread_exit 
Terminate the calling thread and return a value to the joining process if applicable.

```
extern void pthread_exit (void *__retval) __attribute__ ((__noreturn__));
```


## Description
This is the clean way to terminate a thread, called by the thread itself. As a programmer, one would have the thread call pthread_exit when a given thread\'s task is complete

## Parameters
* void *retval: the specified return value of the terminated thread. This is a void * that can be cast to anything if need be. 

## Outputs
* None: Returns Void 

## example code
TODO FIXME

```bash
TODO
```


