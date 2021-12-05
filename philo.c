/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghole <sanghole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 16:28:26 by sanghole          #+#    #+#             */
/*   Updated: 2021/11/29 15:44:54 by sanghole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_error(char *str)
{
	printf("ERROR | ");
	printf("%s\n", str);
	return (-1);
}

int	check_end(t_data *data)
{
	data->check_end = 1;
	return (1);
}

int	check_die(t_data *data)
{
	int	i;

	i = 0;
	while (i < (int) data->c_philo)
	{
		if (data->check_eat == data->c_philo)
			return (check_end(data));
		if ((time_now() - data->philo[i].last_eat_time) > data->t_to_die)
		{
			print_status(&data->philo[i], DIE);
			return (check_end(data));
		}
		i++;
	}
	return (0);
}

int	monitoring(t_data *data)
{
	int	i;

	while (1)
	{
		if (check_die(data))
			break ;
	}
	i = 0;
	while (i < data->c_philo)
	{
		if (pthread_join(data->philo[i].thread, NULL))
			return (free_n_destory(data, "thread join"));
		i++;
	}
	my_usleep(100);
	if (free_n_destory(data, NULL) == -1)
		return (-1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (init_param(argc, argv, &data) == -1)
		return (-1);
	if (init_mutex_philo(&data) == -1)
		return (-1);
	if (create_thread(&data) == -1)
		return (-1);
	if (monitoring(&data) == -1)
		return (-1);
	return (0);
}
