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

	param->last_meal = (int *)malloc(sizeof(int) * param->info[0]);
	if (!param->last_meal)
		return (-1);
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

void init_each(t_param *param, t_each *each)
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
	usleep((param->info[0] + 1 - each->id) * 1000);
	each->start = get_time();
}
