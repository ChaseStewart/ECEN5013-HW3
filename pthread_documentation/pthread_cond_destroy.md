# pthread_cond_destroy 
destroy and free condition variable __cond

```
extern int pthread_cond_destroy (pthread_cond_t *__cond)
     __THROW __nonnull ((1));
```

## Description
This destroys condition variable __cond and frees any resources if need be. The condition must not have any threads waiting on it for destroy to succeed- if there are still threads waiting on this, pthread_cond_destroy will return an error.

## Parameters
* pthread_cond_t *__cond: A pointer to the condition variable of type pthread_cond_t which one wants destroyed

## Outputs
* int: a status variable from the destroy attempt 

## Notes
Think of this as equivalent to a free() of an initialized pthread condition variable. Anything that you pthread_cond_init should be freed via pthread_cond_destroy when you know that the condition variable is no longer needed.

## Example Code
Please see examples/pthread_cond_example.c 
