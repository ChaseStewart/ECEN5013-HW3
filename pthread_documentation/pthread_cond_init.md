# pthread_cond_init
create a condition variable using the provided attributes or else defaults

```
extern int pthread_cond_init (pthread_cond_t *__restrict __cond,
			      const pthread_condattr_t *__restrict __cond_attr)
     __THROW __nonnull ((1));
```

## Description
This function initializes the pthread_cond_t pointed to by __cond using the given parameters in __cond_attr. If 
__cond_attr is blank, pthread_cond_init will use the default parameters to initialize.

## Parameters
* pthread_cond_t *__restrict __cond: the variable where the created cond will be returned
* const pthread_condattr_t *__restrict __cond_attr: the struct that holds the attrs one would like to be initialized in the cond variable 

## Outputs
* int: a status integer 

## Notes
If you plan to use pthread condition variables, this should be called on each variable and checked for success before using pthread_cond_wait or pthread_cond_signal/broadcast

## Example Code
Please see examples/pthread_cond_example.c 
