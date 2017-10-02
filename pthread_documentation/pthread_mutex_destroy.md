# pthread_mutex_destroy 
Destroy the given mutex __mutex and free all resources

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

## example code
to run the command

```bash
int retval;
retval = run_command(parameter1, parameter2);

/* retval should equal 0 */

```


