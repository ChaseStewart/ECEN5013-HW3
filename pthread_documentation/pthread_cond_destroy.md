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

## example code
to run the command

```bash
int retval;
retval = run_command(parameter1, parameter2);

/* retval should equal 0 */

```


