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

## Notes
If this is used, one should *DEFINITELY* check the status of this call and use it to see whether the mutex is grabbed. Also, if one wants the mutex to always be grabbed even if blocking is required, look at pthread_mutex_lock.md. If mutexes need to be used in an interrupt, this would be a good choice.

## Example Code
Please see examples/pthread_mutex_example.c 
