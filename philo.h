#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_param
{
	int info[5];
	pthread_t *tid;
	pthread_mutex_t *mutex;
	suseconds_t now;
	int id;

} t_param;

#endif
