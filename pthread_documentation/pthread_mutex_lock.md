# pthread_mutex_lock
Either lock mutex __mutex or else suspend the thread until __mutex is unlocked again.

```
extern int pthread_mutex_lock (pthread_mutex_t *__mutex)
     __THROWNL __nonnull ((1));
```

## Description
Attempt to lock the mutex- if the mutex is unlocked at that instant, it will become locked and will belong to this calling thread. If the mutex is instead locked, this function call will cause the calling thread to suspend until the mutex is locked. For a non-blocking similar call, please look at pthread_mutex_trylock 

## Parameters
* pthread_mutex_t *__mutex: A handle of the mutex which should be locked.

## Outputs
* int: return the status of pthread_mutex_lock

## example code
to run the command

```bash
int retval;
retval = run_command(parameter1, parameter2);

/* retval should equal 0 */

```


