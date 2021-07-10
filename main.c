#include "philo.h"

int ft_strlen(char *s)
{
	int i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

int t_index(t_param param, pthread_t value)
{
	int i;

	i = -1;
	while (++i < param.info[0])
		if (param.tid[i] == value)
			return (i);
	return (-1);
}

int ft_atoi(char *s)
{
	int num;
	int size;
	int i;

	num = 0;
	i = 0;
	size = ft_strlen(s);
	if (size == 0)
		return (-1);
	if (s[0] == '+')
		i++;
	while (i < size)
	{
		if (!(s[i] >= '0' && s[i] <= '9'))
		       return (-1);
		num *= 10;
		num += s[i] - '0';
		i++;
	}
	return (num);
}

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

void *my_func(void *arg)
{
	t_param *param;
	struct timeval tv_t;
	int id;
	int now;

	param = (t_param *)arg;
	id = param->id;
	now = param->now;
	tv_t.tv_usec = now;
	//printf("%d\n", id);
	usleep((param->info[0] + 1 - id) * 100);
	if (gettimeofday(&tv_t, NULL) == -1)
		return ((void *) -1);
	printf("%d %d\n", id, (int)tv_t.tv_usec);
//	if ((param->id % 2) == 0)

	return (0);
}

int philo(char **argv)
{
	t_param param;
	struct timeval tv;
	int i;

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
	i = 0;
	while (++i <= param.info[0])
	{
		param.id = i;
		if (gettimeofday(&tv, NULL) == -1)
			return (-1);
		param.now = tv.tv_usec;
	//	printf("%d\n", (int)param.now);
		if (pthread_create(&param.tid[i - 1], NULL, my_func, &param) != 0)
			return (-1);
		usleep(100);
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
