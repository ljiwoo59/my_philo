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
	pthread_t m_tid;
	pthread_mutex_t stop;
	pthread_mutex_t *mutex;
	int id;
	int is_dead;
	int *last_meal;

} t_param;

typedef struct s_each
{
	int id;
	int left;
	int right;
	int have_eat;
	double start;
	double end;
} t_each;

int ft_strlen(char *s);
int ft_atoi(char *s);
int set_info(char *s, int i, t_param *param);
int init_param(t_param *param);
void init_each(t_param *param, t_each *each);
double get_time(void);
int take_fork(t_param *param, t_each each);
int eat(t_param *param, t_each each);
int sleeping(t_param *param, t_each each);
int philo(t_param *param);
void *my_func(void *arg);
void *monitoring(void *arg);

#endif
