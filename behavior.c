#include "philo.h"

int o_take_fork(t_param *param, t_each each)
{
//	pthread_mutex_lock(&param->stop);
	if (param->fork[each.left] == 0 && param->fork[each.right] == 0)
	{
//		pthread_mutex_lock(&param->stop);
		if (pthread_mutex_lock(&param->mutex[each.right]) != 0)
			return (-1);
//		pthread_mutex_unlock(&param->stop);
		param->fork[each.right] = 1;
		if (param->is_dead == 0)
		{	
			pthread_mutex_unlock(&param->mutex[each.right]);
			param->fork[each.right] = 0;
			pthread_mutex_unlock(&param->stop);
			return (-1);
		}
		printf("%.f ms philo%d has taken a right fork\n", get_time() - each.start, each.id);
		if (pthread_mutex_lock(&param->mutex[each.left]) != 0)
		{
			pthread_mutex_unlock(&param->mutex[each.right]);
			param->fork[each.right] = 0;
			pthread_mutex_unlock(&param->stop);
			return (-1);
		}
//		pthread_mutex_unlock(&param->stop);
		param->fork[each.left] = 1;
		if (param->is_dead == 0)
		{	
			pthread_mutex_unlock(&param->mutex[each.left]);
			param->fork[each.left] = 0;
			return (-1);
		}
		printf("%.f ms philo%d has taken a left fork\n", get_time() - each.start, each.id);
	//	pthread_mutex_unlock(&param->stop);
		return (1);
	}
	pthread_mutex_unlock(&param->stop);
	return (-1);
}

int e_take_fork(t_param *param, t_each each)
{
//	pthread_mutex_lock(&param->stop);
	if (param->fork[each.left] == 0 && param->fork[each.right] == 0)
	{
		if (pthread_mutex_lock(&param->mutex[each.left]) != 0)
			return (-1);
		param->fork[each.left] = 1;
		if (param->is_dead == 0)
		{	
			pthread_mutex_unlock(&param->mutex[each.left]);
			param->fork[each.left] = 0;
//			pthread_mutex_unlock(&param->stop);
			return (-1);
		}
		printf("%.f ms philo%d has taken a leftfork\n", get_time() - each.start, each.id);
		if (pthread_mutex_lock(&param->mutex[each.right]) != 0)
		{
			pthread_mutex_unlock(&param->mutex[each.left]);
			param->fork[each.left] = 0;
//			pthread_mutex_unlock(&param->stop);
			return (-1);
		}
//		pthread_mutex_unlock(&param->stop);
		param->fork[each.right] = 1;
		if (param->is_dead == 0)
		{	
			pthread_mutex_unlock(&param->mutex[each.right]);
			param->fork[each.right] = 0;
			return (-1);
		}
		printf("%.f ms philo%d has taken a rightfork\n", get_time() - each.start, each.id);
		return (1);
	}
//	pthread_mutex_unlock(&param->stop);
	return (-1);
}

int eat(t_param *param, t_each each)
{
	double start;

	if (param->is_dead == 0)
	{	
		pthread_mutex_unlock(&param->mutex[each.right]);
		pthread_mutex_unlock(&param->mutex[each.left]);
		param->fork[each.right] = 0;
		param->fork[each.left] = 0;
		return (-1);
	}
	printf("%.f ms philo%d is eating\n", get_time() - each.start, each.id);
	param->last_meal[each.id - 1] = 0;
	start = get_time();
	while ((get_time() - start) <= param->info[2])
	{
		if (param->is_dead == 0)
			break;
		usleep(1000);
	}
	if (each.id % 2 == 0)
	{
		pthread_mutex_unlock(&param->mutex[each.right]);
		pthread_mutex_unlock(&param->mutex[each.left]);
	}
	else
	{
		pthread_mutex_unlock(&param->mutex[each.left]);
		pthread_mutex_unlock(&param->mutex[each.right]);
	}
	param->eat_time[each.id - 1]++;
	param->fork[each.right] = 0;
	param->fork[each.left] = 0;
	return(1);
}

int sleeping(t_param *param, t_each each)
{
	double start;

	printf("%.f ms philo%d is sleeping\n", get_time() - each.start, each.id);
	start = get_time();
	while ((get_time() - start) <= param->info[3])
	{
		if (param->is_dead == 0)
			break;
		usleep(1000);
	}
	usleep(2000);
	return (0);
}
