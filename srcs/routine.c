/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarboul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 08:05:33 by mlarboul          #+#    #+#             */
/*   Updated: 2021/06/19 11:56:44 by mlarboul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	start_eating(t_arg *table, t_philo *philos, int i)
{
	printf("%.5ld %d is eating\n",
			(long)(get_timestamp(table->start) / 1E3), philos[i].id);
	my_usleep(philos[i].options->time_to_eat);
	gettimeofday(&philos[i].last_meal, NULL);
	philos[i].meals_nb++;
	pthread_mutex_unlock(&table->mutex[philos[i].l_fork - 1]);
	pthread_mutex_unlock(&table->mutex[philos[i].r_fork - 1]);
	printf("%.5ld %d is sleeping\n",
			(long)(get_timestamp(table->start) / 1E3), philos[i].id);
	my_usleep(philos[i].options->time_to_sleep);
	printf("%.5ld %d is thinking\n",
			(long)(get_timestamp(table->start) / 1E3), philos[i].id);
}

int	grab_fork(t_arg *table, t_philo *philos, int i)
{
	if (i % 2 == 0)
	{
		if (pthread_mutex_lock(&table->mutex[philos[i].r_fork - 1]) != 0)
			return (-1);
		printf("%.5ld %d has taken a fork\n",
				(long)(get_timestamp(table->start) / 1E3), philos[i].id);
	}
	if (pthread_mutex_lock(&table->mutex[philos[i].l_fork - 1]) != 0)
		return (-1);
	printf("%.5ld %d has taken a fork\n", 
			(long)(get_timestamp(table->start) / 1E3), philos[i].id);
	if (i % 2 == 1)
	{
		if (pthread_mutex_lock(&table->mutex[philos[i].r_fork - 1]) != 0)
			return (-1);
		printf("%.5ld %d has taken a fork\n",
				(long)(get_timestamp(table->start) / 1E3), philos[i].id);
	}
	return (0);
}

void	*routine(void *arg)
{
	t_arg		*table;
	t_philo		*philos;
	int			i;

	table = (t_arg *)arg;
	i = table->i;
	philos = table->philos;
	while (*table->all_alive == TRUE)
	{
		if (grab_fork(table, philos, i) == 0)
			start_eating(table, philos, i);
	}
	return (NULL);
}
