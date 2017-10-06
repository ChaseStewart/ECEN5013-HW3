# pthread_mutex_destroy 
Destroy the given mutex __mutex and free all resources associated with it

```
extern int pthread_mutex_destroy (pthread_mutex_t *__mutex)
     __THROW __nonnull ((1));
```

## Description
This function destroys mutex __mutex if possible and frees its resources. The given mutex must be unlocked for this function to succeed- else it will return an error.

# Paraneters
* pthread_mutex_t *__mutex: a handle to the mutex to be destroyed

## Outputs
* int: return int status of pthread_mutex_destroy

## Notes 
Call this on a mutex to destroy it when no longer in use.

## Example Code
Please see examples/pthread_mutex_example.c 
