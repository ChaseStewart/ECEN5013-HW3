# pthread_cond_wait
Cause a pthread to wait for condition variable __cond to be sent

```
extern int pthread_cond_wait (pthread_cond_t *__restrict __cond,
			      pthread_mutex_t *__restrict __mutex)
     __nonnull ((1, 2));
```

## Description
Once this command is called, calling thread will wait until pthread_cond_t __cond is signalled via pthread_cond_signal or broadcast via pthread_cond_broadcast. The calling thread must acquire the mutex __mutex before it calls this function to prevent a race condition caused by a missed handoff of pthread_cond_wait to pthread_cond_signal/broadcast.

## Parameters
* pthread_cond_t *__restrict __cond: the condition variable that this thread will wait() for
* pthread_mutex_t *__restrict __mutex: the mutex associated with the condition variable to prevent race condition issues with wait() and signal/broadcast() 

## Outputs
* int: this int returns the status of the pthread_cond_wait.

## example code
to run the command

```bash
int retval;
retval = run_command(parameter1, parameter2);

/* retval should equal 0 */

```


