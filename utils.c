/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghole <sanghole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 00:18:19 by sanghole          #+#    #+#             */
/*   Updated: 2021/11/29 06:51:55 by sanghole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	else
		return (0);
}

long long	ft_atoi(const char *nptr)
{
	long long	data;
	int			minus;
	int			i;

	data = 0;
	i = 0;
	minus = 1;
	while (nptr[i] != '\0' && ft_isspace(nptr[i]) == 1)
		i++;
	if (nptr[i] == '-')
		minus = -1;
	if ((nptr[i] == '-' || nptr[i] == '+'))
		i++;
	while ((nptr[i] != '\0') && (nptr[i] >= '0') && (nptr[i] <= '9'))
	{
		data = (data * 10) + (nptr[i] - '0');
		if (data > 2147483647 && minus == 1)
			return (-1);
		if (data > 2147483647 && minus == -1)
			return (0);
		i++;
	}
	return (minus * data);
}

long	time_now(void)
{
	struct timeval	curr_time;

	gettimeofday(&curr_time, NULL);
	return ((curr_time.tv_sec * 1000) + (curr_time.tv_usec / 1000));
}

void	my_usleep(long time)
{
	long	start;

	start = time_now();
	while ((time_now() - time) < start)
	{
		usleep(100);
	}
}

int	print_status(t_philo *ph, int data)
{
	char	*str;

	pthread_mutex_lock(&ph->data->print);
	if (ph->data->check_end)
	{
		pthread_mutex_unlock(&ph->data->print);
		return (1);
	}
	if (data == FORK)
		str = "has taken a fork";
	if (data == EAT)
		str = "is eating";
	if (data == SLEEP)
		str = "is sleeping";
	if (data == THINK)
		str = "is thinking";
	if (data == DIE)
		str = "died";
	printf("%ld %d %s\n", time_now() - ph->data->start_time, ph->id + 1, str);
	pthread_mutex_unlock(&ph->data->print);
	return (0);
}
