/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarboul <mlarboul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 11:23:30 by mlarboul          #+#    #+#             */
/*   Updated: 2021/06/24 12:26:05 by mlarboul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	start_eating(t_arg *table, t_philo *philos, int i)
{
	print_status(EATING, table, philos, i);
	gettimeofday(&philos[i].last_meal, NULL);
	my_usleep(philos[i].options->time_to_eat, table);
	pthread_mutex_lock(table->meals_mtx);
	philos[i].meals_nb++;
	pthread_mutex_unlock(table->meals_mtx);
	pthread_mutex_unlock(&table->mutex[philos[i].l_fork - 1]);
	pthread_mutex_unlock(&table->mutex[philos[i].r_fork - 1]);
	print_status(SLEEPING, table, philos, i);
	my_usleep(philos[i].options->time_to_sleep, table);
	print_status(THINKING, table, philos, i);
}

int	grab_fork(t_arg *table, t_philo *philos, int i)
{
//	if (i % 2 != 0)
//	{
		pthread_mutex_lock(&table->mutex[philos[i].r_fork - 1]);
		print_status(FORK, table, philos, i);
//	}
	pthread_mutex_lock(&table->mutex[philos[i].l_fork - 1]);
	print_status(FORK, table, philos, i);
//	if (i % 2 == 0)
//	{
//		pthread_mutex_lock(&table->mutex[philos[i].r_fork - 1]);
//		print_status(FORK, table, philos, i);
//	}
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
			break;
		if (grab_fork(table, philos, i) == 0)
			start_eating(table, philos, i);
		j++;
	}
	return (NULL);
}
