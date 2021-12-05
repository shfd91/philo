/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_n_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghole <sanghole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 14:26:55 by sanghole          #+#    #+#             */
/*   Updated: 2021/11/29 15:44:29 by sanghole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_num(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	init_param(int argc, char **argv, t_data *data)
{
	if (argc < 5 || argc > 6)
		return (print_error("invalid parameter"));
	if (check_num(argc, argv))
		return (print_error("parameter is number only"));
	data->fork = NULL;
	data->philo = NULL;
	data->c_philo = ft_atoi(argv[1]);
	data->t_to_die = ft_atoi(argv[2]);
	data->t_to_eat = ft_atoi(argv[3]);
	data->t_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		data->must_eat = ft_atoi(argv[5]);
		if (data->must_eat <= 0)
			return (print_error("must_eat is positive number"));
	}
	else
		data->must_eat = -1;
	if (data->c_philo < 1 || data->t_to_die < 1 \
		|| data->t_to_eat < 1 || data->t_to_sleep < 1 \
		|| data->must_eat == 0)
		return (print_error("invalid parameter"));
	return (0);
}

void	init_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->c_philo)
	{
		data->philo[i].id = i;
		data->philo[i].data = data;
		data->philo[i].eat_count = data->must_eat;
		data->philo[i].last_eat_time = data->start_time;
		i++;
	}
}

int	init_fork(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->c_philo)
	{
		if (pthread_mutex_init(&data->fork[i], NULL))
			return (destroy_forks(data, i));
		i++;
	}
	return (0);
}

int	init_mutex_philo(t_data *data)
{
	data->check_end = 0;
	data->philo = (t_philo *)malloc(sizeof(t_philo) * data->c_philo);
	if (!data->philo)
		return (print_error("memory alloc"));
	data->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * \
		data->c_philo);
	if (!data->fork)
	{
		free(data->philo);
		return (print_error("memory alloc"));
	}
	if (pthread_mutex_init(&data->print, NULL))
	{
		free_alloc(data);
		return (print_error("mutex init"));
	}
	if (init_fork(data) == -1)
		return (-1);
	data->start_time = time_now();
	data->check_eat = 0;
	init_philo(data);
	return (0);
}
