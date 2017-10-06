# pthread_getattr_default_np 
Get the default attributes for a pthread in this function

```
extern int pthread_getattr_default_np (pthread_attr_t *__attr)
     __THROW __nonnull ((1));
```

## Description
Since pthread_setattr_np() is able to set the default attributes for a new thread, this function is a check on that one, returning the current state a new pthread will inherit via the passed in pthread_attr_t pointer.

## Parameters
* pthread_attr_t *__attr: The default attributes for a pthread will be placed into the object pointed to by this arg

## Outputs
* extern int: Return the status of this command

## Notes
This one is pretty self-explanatory, this command tells you what kind of pthread will be created when the pthread_attr_t arg in pthread_create() is NULL- however the man pages offer some details for this- the stack address should not be set, and there should be no invalid attribute settings in the provided object

## Example Code
Please see examples/pthread_example.c 
