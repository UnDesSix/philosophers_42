/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarboul <mlarboul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 11:23:30 by mlarboul          #+#    #+#             */
/*   Updated: 2021/06/25 09:04:29 by mlarboul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_bool	everyone_ate(t_arg *arg, t_opt *options)
{
	int	i;

	i = 0;
	while (i < options->philo_nb)
	{
		pthread_mutex_lock(arg->meals_mtx);
		if (options->extra_nb > arg->philos[i].meals_nb)
		{
			pthread_mutex_unlock(arg->meals_mtx);
			return (FALSE);
		}
		pthread_mutex_unlock(arg->meals_mtx);
		i++;
	}
	return (TRUE);
}

t_bool	end_conditions(t_arg *arg, t_opt *options)
{
	int	i;

	i = 0;
	while (i < options->philo_nb)
	{
		if (options->extra_nb >= 0 && everyone_ate(arg, options) == TRUE)
		{
			pthread_mutex_lock(arg->alive_mtx);
			*arg->all_alive = FALSE;
			pthread_mutex_unlock(arg->alive_mtx);
			print_status(ALL_ATE, arg, arg->philos, i);
			return (TRUE);
		}
		if (get_timestamp(arg->philos[i].last_meal) >
				options->time_to_die)
		{
			pthread_mutex_lock(arg->alive_mtx);
			*arg->all_alive = FALSE;
			pthread_mutex_unlock(arg->alive_mtx);
			print_status(DEAD, arg, arg->philos, i);
			if (options->philo_nb == 1)
				pthread_mutex_unlock(&arg->mutex[arg->philos[i].r_fork - 1]);
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

void	start_eating(t_arg *table, t_philo *philos, int i)
{
	print_status(EATING, table, philos, i);
	gettimeofday(&philos[i].last_meal, NULL);
	my_usleep(philos[i].options->time_to_eat, table);
	pthread_mutex_unlock(&table->mutex[philos[i].l_fork - 1]);
	pthread_mutex_unlock(&table->mutex[philos[i].r_fork - 1]);
	print_status(SLEEPING, table, philos, i);
	pthread_mutex_lock(table->meals_mtx);
	philos[i].meals_nb++;
	pthread_mutex_unlock(table->meals_mtx);
	my_usleep(philos[i].options->time_to_sleep, table);
	print_status(THINKING, table, philos, i);
}

int	grab_fork(t_arg *table, t_philo *philos, int i)
{
	pthread_mutex_lock(&table->mutex[philos[i].r_fork - 1]);
	print_status(FORK, table, philos, i);
	if (table->philos->options->philo_nb <= 1)
		return (-1);
	pthread_mutex_lock(&table->mutex[philos[i].l_fork - 1]);
	print_status(FORK, table, philos, i);
	return (0);
}

void	*routine(void *arg)
{
	t_arg		*table;
	t_philo		*philos;
	int			i;
	int			j;

	table = (t_arg *)arg;
	i = table->i;
	philos = table->philos;
	j = 0;
	while (is_alive(table) == TRUE)
	{
		if (philos->options->extra_nb > 0 && j >= philos->options->extra_nb)
			break ;
		if (grab_fork(table, philos, i) == 0)
			start_eating(table, philos, i);
		j++;
	}
	return (NULL);
}
