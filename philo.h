#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <time.h>
# include <pthread.h>

typedef struct s_param
{
	int info[5];
	pthread_t tid;
	pthread_mutex_t mutex;
	int id;

} t_param;


#endif
