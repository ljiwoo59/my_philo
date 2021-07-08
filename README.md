# my_philo
Dining philosophers problem

```linux
$> ./philo  number_of_philos  time_to_die  time_to_eat  time_to_sleep  [number_of_times_each_philo_must_eat]
```

* **number_of_philosophers**  
The number of philosophers and also the number of forks.

* **time_to_die**  
After starting his last meal or the beginning of the simulation, if a philosopher doesn’t start eating in *time_to_die* milliseconds, it dies.

* **time_to_eat**  
The time in milliseconds that takes for a philosopher to eat.  
During that time he will need to keep the two forks.

* **time_to_sleep**  
The time in milliseconds that a philosopher sleeps.

* **number_of_times_each_philosopher_must_eat** *(Optional)*  
If all philosophers eat at least *number_of_times_each_philosopher_must_eat*, the simulation will stop.  
If not specified, the simulation will stop only at the death of a philosopher.  

---

## What is Thread?
* A **thread** is a single sequential flow of control within a program.
* A **process** can contain one or multiple *threads*.
* While **processes** run in separate memory spaces, **threads** within the same *process* run in a shared memory space.
* **Threads** share code section, data section, and OS resources with other threads.
* **Thread** has its own program counter (PC), register set, and stack space.

## What is Mutex?
* **Mut**ual **Ex**clusion
* Gives access to only one of the *threads/processes* at a time.
* Common issue : **Deadlock**
  - A situation where a set of processes are blocked because each process is holding a resource and waiting for another resource acquired by some other process.

---

## Used Functions

#### *void \*memset(void \*b, int c, size_t len);*
* Writes *len* bytes of value *c* to the string *b* (continuously).
* Returns its first argument.

#### *int usleep(useconds_t microseconds);*
* Suspends execution of the calling thread until either microseconds have elapsed or a signal is delivered to the thread and its action is to invoke a signal-catching function or to terminate the process.
* Returns 0 if success, otherwise -1 with errno.

#### *int gettimeofday(struct timeval \*restrict tp, void \*restrict tzp);*
```c
struct timeval {
             time_t       tv_sec;   /* seconds since Jan. 1, 1970 */
             suseconds_t  tv_usec;  /* and microseconds */
};

struct timezone {
             int     tz_minuteswest; /* of Greenwich */
             int     tz_dsttime;     /* type of dst correction to apply */
};
```
* The current Greenwich time and the current time zone is obtained.
  - If *tp* is NULL and *tzp* is non-NULL, will populate the timezone struct in *tzp*.
  - If *tp* is non-NULL and *tzp* is NULL, then only the timeval struct in *tp* is populated.
  - If both *tp* and *tzp* are NULL, nothing is returned.
* Returns 0 if success, otherwise -1 with errno.

#### *int pthread_create(pthread \*thread, const pthread_attr_t \*attr, void \*(\*start_routine)(void \*), void \*arg);*
* Creates a new thread, with attributes specified by *attr*, within a process.
  - If *attr* is NULL, the default attributes are used.
  - If the attributes specified by *attr* are modified later, the thread's attributes are not affected.  
  - Upon successful completion, will store the *ID* of the created thread in the location specified by *thread*.
* Returns 0 if success, otherwise error number.

#### *int pthread_detach(pthread_t thread);*
* Indicates to the implementation that storage for the thread thread can be reclaimed when the thread terminates.
* Returns 0 if success, otherwise error number.

#### *int pthread_join(pthread_t thread, void \*\*value_ptr);*
* Suspends execution of the calling thread until the target thread terminates unless the target thread has already terminated.
  - Value passed to pthread_exit() by the terminating thread is stored in the location referenced by *value_ptr*.
* Returns 0 if success, otherwise error number.

#### *int pthread_mutex_init(pthread_mutex_t \*mutex, const pthread_mutexattr_t \*attr);*
* Creates a new mutex, with attributes specified with attr.
  - If *attr* is NULL the default attributes are used.
* Returns 0 and put the new *mutex id* into *mutex*, otherwise error number.

#### *int pthread_mutex_destroy(pthread_mutex_t \*mutex);*
* Frees the resources allocated for mutex.
* Returns 0 if success, otherwise error number.

#### *int pthread_mutex_lock(pthread_mutex_t \*mutex);*
* Locks mutex.
* Returns 0 if success, otherwise error number.
#### *int pthread_mutex_unlock(pthread_mutex_t \*mutex);*
* Unlocks mutex.
* Returns 0 if success, otherwise error number.
