#include "philo.h"

void *my_func(void *arg)
{
	t_param *param;
	t_each each;
	int id;
	double init;
	int have_eat;

	param = (t_param *)arg;
	id = param->id;
	if (id == 1)
		each.left = 0;
	else
		each.left = id - 1;
	if (id == param->info[0])
		each.right = 0;
	else
		each.right = id;
	usleep((param->info[0] + 1 - id) * 100);
	init = get_time();
	int stop = 5;
	while(stop--)
	{
		if (take_fork(param, id, init, each))
			have_eat = eat(param, id, init, each);
		if (have_eat == 0)
			sleeping(param, id, init);
		printf("%.f ms philo%d is thinking\n", get_time() - init, id);
	}
	return (0);
}

int philo(char **argv)
{
	t_param param;
	int i;

	pthread_mutex_init(&param.stop, NULL);
	
	i = 0;
	while (++i < 5)
		if (set_info(argv[i], i - 1, &param) == -1)
			return (-1);
	param.tid = (pthread_t *)malloc(sizeof(pthread_t) * param.info[0]);
	if (!param.tid)
		return (-1);
	param.mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * param.info[0]);
	if (!param.mutex)
		return (-1);
	i = 0;
	while (i < param.info[0])
		if (pthread_mutex_init(&param.mutex[i++], NULL) != 0)
				return (-1);
	param.init_d = 0;
	i = 0;
	while (++i <= param.info[0])
	{
		param.id = i;
		if (pthread_create(&param.tid[i - 1], NULL, my_func, &param) != 0)
			return (-1);
		usleep(1000);
	}	
	i = 0;
	while (i < param.info[0])
		if (pthread_join(param.tid[i++], NULL) != 0)
			return (-1);
	return (0);
}

int main(int argc, char **argv)
{
	if (argc == 5)
		if (philo(argv) == -1)
		{
			printf("Error");
			return (1);
		}
	/*
	else if (argc == 6)
		if (philo_time(argv) == -1)
			return (1);
	*/
	return (0);
}
