#include "philo.h"

int ft_strlen(char *s)
{
	int i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
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
	if (num <= 0)
		return (-1);
	param->info[i] = num;
	return (0);
}

void *my_func(void *arg)
{
	t_param *param;

	param = (t_param *)arg;
	printf("%d\n", param->id);
//	if ((param->id % 2) == 0)

	return (0);
}

int philo(char **argv)
{
	t_param param;
	int i;

	i = 0;
	while (++i < 5)
		if (set_info(argv[i], i - 1, &param) == -1)
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
		if (pthread_create(&param.tid, NULL, my_func, &param) != 0)
			return (-1);
		usleep(100);
	}
	i = -1;
	if (pthread_join(param.tid, NULL) != 0)
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
