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

int set_info(char *s, int i, int *info)
{
	int num;

	num = ft_atoi(s);
	if (num < 0)
		return (-1);
	info[i] = num;
	return (0);
}

int philo(char **argv)
{
	int info[4];
	int i;

	i = 0;
	while (++i < 5)
		if (set_info(argv[i], i - 1, info) == -1)
			return (-1);
	
	for(int j = 0; j < 4; j++)
		printf("%d ", info[j]);

	return (0);
}

int main(int argc, char **argv)
{
	if (argc == 5)
		if (philo(argv) == -1)
			return (1);
	/*
	else if (argc == 6)
		if (philo_time(argv) == -1)
			return (1);
	*/
	return (0);
}
