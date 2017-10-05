# pthread_getattr_np
Get pthread_attr_t attributes from a currently-running thread and place them into uninitialized pthread_attr_t.

```
extern int pthread_getattr_np (pthread_t __th, pthread_attr_t *__attr)
     __THROW __nonnull ((2));
```

## Description
This function first initializes pthread_attr_t __attr, then takes the current pthread_attr_t of the thread __th and copies it into __attr. This is useful to know the current state of __th's attributes. __th should be initialized before this is called, but __attr should NOT be initialized before this is called.

## Parameters
* pthread_t __th: This is the thread whose attributes you would like to copy to __attr
* pthread_attr_t *__attr: an uninitialized pthread_attr_t pointer which will be filled with the pthread_attr_t

## Outputs
* extern int: return value of function call

## Notes
The manpages state that the attributes returned by this function MAY NOT BE the same attributes which were passed in at initialization. They also emphasize that pthread_attr_ts formed in this way should be destroyed with pthread_attr_destroy() when one is done with them.

