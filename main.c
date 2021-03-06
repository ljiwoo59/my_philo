#include "philo.h"

void *monitoring(void *arg)
{
	t_param *param;
	int i;
	int locks;
	double start;
	double init;

	param = (t_param *)arg;

	usleep(2000 * (param->info[0] - 1));
	init = get_time();
	while (param->is_dead)
	{
		start = get_time();
		while ((get_time() - start) < 1)
			usleep(1);
		if (param->six == 1 && check_eat(param) == 1)
		{
			param->is_dead = 0;
			break;
		}
		i = 0;
		while (i < param->info[0])
		{
			param->last_meal[i] += 1;
			if (param->last_meal[i] >= param->info[1])
			{
				param->is_dead = 0;
				printf("%.f ms philo%d died\n", get_time() - init, i + 1);
				locks = param->info[1];
				while (locks)
					pthread_mutex_unlock(&param->mutex[locks--]);
				break;
			}
			i++;
		}
	}
	return (0);
}

void *my_func(void *arg)
{
	t_param *param;
	t_each each;
	int ret;

	param = (t_param *)arg;
	if (!init_each(param, &each))
	{
		while(param->is_dead)
		{
		}
	}
	else
	{
		while(param->is_dead)
		{
			each.have_eat = 0;
			if (param->is_dead)
			{
				//if (each.id % 2 == 0)
				pthread_mutex_lock(&param->stop);
				ret = e_take_fork(param, each);
				pthread_mutex_unlock(&param->stop);
				//else
				//	ret = o_take_fork(param, each);
				if (ret == 1)
				{
					eat(param, each);
					if (param->is_dead)
						sleeping(param, each);
					if (param->is_dead)
						printf("%.f ms philo%d is thinking\n", get_time() - each.start, each.id);
				}
			}
		}
	}
	return (0);
}

int philo(t_param *param)
{
	int i;

	pthread_mutex_init(&param->stop, NULL);
	
	if (pthread_create(&param->m_tid, NULL, monitoring, param) != 0)
		return (-1);
	pthread_detach(param->m_tid);

	i = 0;
	while (++i <= param->info[0])
	{
		param->id = i;
		if (pthread_create(&param->tid[i - 1], NULL, my_func, param) != 0)
			return (-1);
		usleep(1000);
	}	
	i = 0;
	while (i < param->info[0])
		if (pthread_join(param->tid[i++], NULL) != 0)
			return (-1);
	return (0);
}

int main(int argc, char **argv)
{
	t_param param;
	int i;

	param.six = 0;
	if (argc == 5 || argc == 6)
	{
		if (argc == 6)
			param.six = 1;
		i = 0;
		while (++i < argc)
			if (set_info(argv[i], i - 1, &param) == -1)
				return (1);
		if (init_param(&param) != 0)
			return (1);
		if (philo(&param) == -1)
		{
			printf("Error");
			return (1);
		}
	}
	return (0);
}
