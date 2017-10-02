# pthread_self
return the pthread_t ID of the calling thread

```
extern pthread_t pthread_self (void) __THROW __attribute__ ((__const__));
```

## Description
As there is no way for pthread_create to give the created thread its pthread_t ID, the created thread can and should use pthread_self to retrieve its pthread_t ID

## Parameters
* None

## Outputs
* pthread_t: the pthread_t type ID of the calling thread.

## example code
TODO FIXME

```bash
TODO FIXME
```


