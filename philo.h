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
	pthread_mutex_t stop;
	pthread_mutex_t *mutex;
	suseconds_t now;
	int init_d;
	int id;

} t_param;

typedef struct s_each
{
	int left;
	int right;
	double start;
	double end;
} t_each;

int ft_strlen(char *s);
int ft_atoi(char *s);
int set_info(char *s, int i, t_param *param);
double get_time(void);
int take_fork(t_param *param, int id, long long init, t_each each);
int eat(t_param *param, int id, long long init, t_each each);
int sleeping(t_param *param, int id, long long init);

#endif
