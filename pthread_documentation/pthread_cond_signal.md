# pthread_cond_signal 
Wake up a thread that is waiting on condition __cond.

```
extern int pthread_cond_signal (pthread_cond_t *__cond)
     __THROWNL __nonnull ((1));
```

## Description
This function wakes up up-to-one thread which is waiting on condition __cond. If more than one thread is waiting on __cond, then one is guaranteed to be awoken, but there is no guarantee on which of the waiting threads. If there are zero threads waiting on __cond, then nothing will happen but the function will not return an error.

## Parameters
* pthread_cond_t *__cond: a handle to the condition __cond to signal.

## Outputs
* int: an int of the return status of pthread_cond_signal

## Notes 
In order for this to function properly, it should be called on a pthread_condition_variable that has been initialized but not destroyed, and it should have a pthread at least attempting to wait for it (if none is waiting, this will just return, but if there is *never* a pthread waiting for this signal, you should re-evaluate your design). As for the difference between choosing cond_signal and cond_broadcast, ask yourself this: do you want this signal to wake up ANY ONE waiting thread or ALL waiting threads?
