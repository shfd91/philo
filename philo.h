/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghole <sanghole@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 16:28:24 by sanghole          #+#    #+#             */
/*   Updated: 2021/11/29 15:31:37 by sanghole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define THINK	0
# define EAT	1
# define SLEEP	2
# define FORK	3
# define DIE	4

# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct s_philo
{
	pthread_t		thread;
	struct s_data	*data;
	int				id;
	long			last_eat_time;
	int				eat_count;
}	t_philo;

typedef struct s_data
{
	t_philo			*philo;
	pthread_mutex_t	*fork;
	pthread_mutex_t	print;
	long			c_philo;
	long			t_to_die;
	long			t_to_eat;
	long			t_to_sleep;
	long			must_eat;
	long			start_time;
	int				check_eat;
	int				check_end;
}	t_data;

/*
	philosophes.c
*/
int			print_error(char *str);

/*
	utils.c
*/
long long	ft_atoi(const char *nptr);
long		time_now(void);
void		my_usleep(long time);
int			print_status(t_philo *ph, int status);

/*
	check_n_init.c
*/
int			init_param(int argc, char **argv, t_data *status);
int			init_mutex_philo(t_data *status);

/*
	lift_cycle.c
*/
void		*life_cycle(void *philo);
int			create_thread(t_data *status);
/*
	free_destory.c
 */
void		free_alloc(t_data *data);
int			destroy_forks(t_data *data, int num);
int			free_n_destory(t_data *data, char *str);
int			get_forks(t_philo *ph, int status);

#endif