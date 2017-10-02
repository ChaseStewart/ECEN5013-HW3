# pthread_mutex_trylock
Either lock mutex __mutex or else instantly return an error code without blocking 

```
extern int pthread_mutex_trylock (pthread_mutex_t *__mutex)
     __THROWNL __nonnull ((1));
```

## Description
Attempt to lock the mutex- if the mutex is unlocked at that instant, it will become locked and will belong to this calling thread, and this function will return success. If the mutex is locked at that instant, this function will not block- it will instead return with an error code for EBUSY.  

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




