/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_cycle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghole <sanghole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 14:38:40 by sanghole          #+#    #+#             */
/*   Updated: 2021/12/06 17:08:18 by sanghole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *ph)
{
	if (ph->eat_count > 0)
	{
		ph->eat_count--;
		if (ph->eat_count == 0)
			ph->data->check_eat++;
	}
	print_status(ph, EAT);
	pthread_mutex_lock(&ph->data->eat_lock);
	ph->last_eat_time = time_now();
	pthread_mutex_unlock(&ph->data->eat_lock);
	my_usleep(ph->data->t_to_eat);
}

void	*life_cycle(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;
	while (ph->data->check_end == 0)
	{
		pthread_mutex_lock(&ph->data->fork[ph->id]);
		if (print_status(ph, FORK))
			return (NULL);
		pthread_mutex_lock(&ph->data->fork[(ph->id + 1) % ph->data->c_philo]);
		if (print_status(ph, FORK))
			return (NULL);
		eat(ph);
		pthread_mutex_unlock(&ph->data->fork[ph->id]);
		pthread_mutex_unlock(&ph->data->fork[(ph->id + 1) % ph->data->c_philo]);
		if (print_status(ph, SLEEP))
			return (NULL);
		my_usleep(ph->data->t_to_sleep);
		if (print_status(ph, THINK))
			return (NULL);
	}
	return (NULL);
}

void	*eat_alone(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;
	pthread_mutex_lock(&ph->data->fork[ph->id]);
	print_status(ph, FORK);
	my_usleep(ph->data->t_to_die);
	pthread_mutex_unlock(&ph->data->fork[ph->id]);
	return (NULL);
}

int	philo_alone(t_data *data)
{
	if (pthread_create(&data->philo[0].thread, NULL, \
		eat_alone, &data->philo[0]))
		return (free_n_destory(data, "thread create"));
	return (0);
}

int	create_thread(t_data *data)
{
	int			i;

	i = 0;
	if (data->c_philo == 1)
		return (philo_alone(data));
	while (i < data->c_philo)
	{
		if (pthread_create(&data->philo[i].thread, NULL, \
		life_cycle, &data->philo[i]))
			return (free_n_destory(data, "thread create"));
		i += 2;
	}
	my_usleep(1);
	i = 1;
	while (i < data->c_philo)
	{
		if (pthread_create(&data->philo[i].thread, NULL, \
			life_cycle, &data->philo[i]))
			return (free_n_destory(data, "thread create"));
		i += 2;
	}
	return (0);
}
