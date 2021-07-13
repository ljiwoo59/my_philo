#include "philo.h"

int take_fork(t_param *param, t_each each)
{
	if (pthread_mutex_lock(&param->mutex[each.left]) != 0)
		return (-1);
//	pthread_mutex_lock(&param->stop);
	if (param->is_dead == 0)
	{	
		pthread_mutex_unlock(&param->mutex[each.left]);
		return (-1);
	}
	printf("%.f ms philo%d has taken a leftfork\n", get_time() - each.start, each.id);
//	pthread_mutex_unlock(&param->stop);
	if (pthread_mutex_lock(&param->mutex[each.right]) != 0)
	{
		pthread_mutex_unlock(&param->mutex[each.left]);
		return (-1);
	}
	if (param->is_dead == 0)
	{	
		pthread_mutex_unlock(&param->mutex[each.right]);
		return (-1);
	}
//	pthread_mutex_lock(&param->stop);
	printf("%.f ms philo%d has taken a rightfork\n", get_time() - each.start, each.id);
//	pthread_mutex_unlock(&param->stop);
	return (1);
}

int eat(t_param *param, t_each each)
{
	double start;

//	pthread_mutex_lock(&param->stop);
	if (param->is_dead == 0)
	{	
		pthread_mutex_unlock(&param->mutex[each.right]);
		pthread_mutex_unlock(&param->mutex[each.left]);
		return (-1);
	}
	printf("%.f ms philo%d is eating\n", get_time() - each.start, each.id);
	param->last_meal[each.id - 1] = 0;
//	pthread_mutex_unlock(&param->stop);
//	usleep(param->info[2] * 1000);
	start = get_time();
	while ((get_time() - start) <= param->info[2])
	{
		if (param->is_dead == 0)
			break;
		usleep(1000);
	}
	pthread_mutex_unlock(&param->mutex[each.right]);
	pthread_mutex_unlock(&param->mutex[each.left]);
	return(0);
}

int sleeping(t_param *param, t_each each)
{
	double start;

//	pthread_mutex_lock(&param->stop);
	printf("%.f ms philo%d is sleeping\n", get_time() - each.start, each.id);
//	pthread_mutex_unlock(&param->stop);
//	usleep(param->info[3] * 1000);
	start = get_time();
	while ((get_time() - start) <= param->info[3])
	{
		if (param->is_dead == 0)
			break;
		usleep(1000);
	}
	return (0);
}
