# pthread_setattr_default_np
Set the default attributes for a pthread

```
extern int pthread_setattr_default_np (const pthread_attr_t *__attr)
     __THROW __nonnull ((1));
```

## Description
This function takes in a pthread_attr_t pointer, and then sets the default for all new pthreads created in this process. Default here means that if a pthread is called with the pthread_attr_t struct set to NULL, then it will inherit the attrs from either the global defaults (if this was never called) or the latest call to this function.

## Parameters
*Parameter 1: does something

## Outputs
* extern int: return status of call

## Notes
Once again pretty straightforward, initialize a pthread_attr_t pointer with the values one desires to be the default, then call this before initializing all threads.
