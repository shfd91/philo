/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_destory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghole <sanghole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 06:10:05 by sanghole          #+#    #+#             */
/*   Updated: 2021/11/29 15:44:14 by sanghole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_alloc(t_data *data)
{
	free(data->fork);
	free(data->philo);
}

int	destroy_forks(t_data *data, int num)
{
	int	i;

	i = 0;
	while (i < num - 1)
	{
		if (pthread_mutex_destroy(&data->fork[i]))
			return (print_error("mutex_destory"));
		i++;
	}
	free_alloc(data);
	return (print_error("mutex_init fork"));
}

int	free_n_destory(t_data *data, char *str)
{
	int	i;

	i = 0;
	while (i < data->c_philo)
	{
		if (pthread_mutex_destroy(&data->fork[i]))
			print_error("mutex_destory");
		i++;
	}
	if (pthread_mutex_destroy(&data->print))
		print_error("mutex_destory");
	free(data->fork);
	free(data->philo);
	if (str)
		return (print_error(str));
	else
		return (0);
}

int	get_forks(t_philo *ph, int status)
{
	if (ph->data->check_end)
	{
		pthread_mutex_unlock(&ph->data->fork[ph->id]);
		if (status == 1)
			pthread_mutex_unlock(&ph->data->fork[(ph->id + 1) % \
				ph->data->c_philo]);
		return (1);
	}
	else
	{
		if (print_status(ph, FORK))
			return (1);
	}
	return (0);
}
