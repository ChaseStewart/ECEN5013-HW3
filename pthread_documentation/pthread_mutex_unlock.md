# pthread_mutex_unlock
Attempt to unlock mutex __mutex 

```
extern int pthread_mutex_unlock (pthread_mutex_t *__mutex)
     __THROWNL __nonnull ((1));
```

## Description
Attempt to unlock the mutex- depending on the type of mutex, this function will either check whether the mutex is locked and owned by the caller (the combination of these is proper state for a call to mutex_unlock), or just blindly set it to unlocked. If the mutex type does check the ownership and lock-state of the mutex and finds either to be improper for this call, it will return an error.

## Parameters
* pthread_mutex_t *__mutex: A handle of the mutex which should be unlocked.

## Outputs
* int: return the status of pthread_mutex_unlock

## Notes
Once again and just like all pthread-related functions, one should *really* check the return status of the function to ensure everything is going according to plan.

## Example Code
Please see examples/pthread_mutex_example.c 
