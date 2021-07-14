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

double get_time(void)
{
	struct timeval tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (-1);

	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int check_eat(t_param *param)
{
	int i;

	i = 0;
	while (i < param->info[0])
	{
		if (param->eat_time[i++] < param->info[4])
			return (-1);
	}
	return (1);
}
