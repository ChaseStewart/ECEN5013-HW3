# pthread_mutex_init
Initialize mutex __mutex with attributes __mutexattr or else default attributes.

```
extern int pthread_mutex_init (pthread_mutex_t *__mutex,
			       const pthread_mutexattr_t *__mutexattr)
     __THROW __nonnull ((1));
```

## Description
This function initializes the mutex object pointed to by __mutex using the attributes in struct __mutexattr. If __mutexattr is null, default attributes are used. This function always succeeds

## Parameters
* pthread_mutex_t *__mutex: a pointer to the mutex to be initialized
* pthread_mutexattr_t *__mutexattr: a pointer to the struct holding attributes with the to-be-created mutex

## Outputs
* int: return the status of pthread_mutex_init 

## example code
to run the command

```bash
int retval;
retval = run_command(parameter1, parameter2);

/* retval should equal 0 */

```


