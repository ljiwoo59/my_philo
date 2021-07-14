#include "philo.h"

int set_info(char *s, int i, t_param *param)
{
	int num;

	num = ft_atoi(s);
	if (i == 0 && num <= 0)
		return (-1);
	if (i && num < 0)
		return (-1);
	param->info[i] = num;
	return (0);
}

int init_param(t_param *param)
{
	int i;

	if (param->six == 1)
	{
		param->eat_time = (int *)malloc(sizeof(int) * param->info[0]);
		if (!param->eat_time)
			return (-1);
		i = 0;
		while (i < param->info[0])
			param->eat_time[i++] = 0;
	}
	param->last_meal = (int *)malloc(sizeof(int) * param->info[0]);
	if (!param->last_meal)
		return (-1);
	param->fork = (int *)malloc(sizeof(int) * param->info[0]);
	if (!param->fork)
		return (-1);
	i = 0;
	while (i < param->info[0])
		param->fork[i++] = 0;
	param->tid = (pthread_t *)malloc(sizeof(pthread_t) * param->info[0]);
	if (!param->tid)
		return (-1);
	param->mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * param->info[0]);
	if (!param->mutex)
		return (-1);
	i = 0;
	while (i < param->info[0])
		if (pthread_mutex_init(&param->mutex[i++], NULL) != 0)
			return (-1);
	param->is_dead = 1;
	return (0);
}

int init_each(t_param *param, t_each *each)
{
	each->id = param->id;
	param->last_meal[each->id - 1] = 0;
	if (each->id == 1)
		each->left = 0;
	else
		each->left = each->id - 1;
	if (each->id == param->info[0])
		each->right = 0;
	else
		each->right = each->id;
	if (each->left == each->right)
		return (0);
	usleep((param->info[0] + 1 - each->id) * 1000);
	each->start = get_time();
	return (1);
}
