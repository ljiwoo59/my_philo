#include "philo.h"

int eat(t_param *param, int id, long long init)
{
	t_each each;

	if (id == 1)
		each.left = param->info[0] - 1;
	else
		each.left = id - 2;
	if (id == param->info[0])
		each.right = 0;
	else
		each.right = id;
		
	if (pthread_mutex_lock(&param->mutex[each.left]) != 0)
		return (-1);
	printf("%.0f ms philo%d has taken a leftfork\n", get_time() - init, id);
	usleep(1);
	if (pthread_mutex_lock(&param->mutex[each.right]) != 0)
	{
		pthread_mutex_unlock(&param->mutex[each.left]);
		return (-1);
	}
	printf("%.0f ms philo%d has taken a rightfork\n", get_time() - init, id);
	usleep(1);
	printf("%.0f ms philo%d is eating\n", get_time() - init, id);
	usleep(param->info[2] * 1000);
	pthread_mutex_unlock(&param->mutex[each.left]);
	pthread_mutex_unlock(&param->mutex[each.right]);
	printf("%.0f ms philo%d is sleeping\n", get_time() - init, id);
	usleep(param->info[3] * 1000);
	return(0);
}
