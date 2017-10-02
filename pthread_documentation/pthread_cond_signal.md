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

## example code
to run the command

```bash
int retval;
retval = run_command(parameter1, parameter2);

/* retval should equal 0 */

```


