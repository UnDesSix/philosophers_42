/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarboul <mlarboul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 11:23:30 by mlarboul          #+#    #+#             */
/*   Updated: 2021/06/23 16:51:54 by mlarboul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	start_eating(t_arg *table, t_philo *philos, int i)
{
//	if (*table->all_alive == TRUE)
//		printf("%.5ld %d is eating\n",
//				get_timestamp(table->start), philos[i].id);
	print_status(EATING, table, philos, i);
	gettimeofday(&philos[i].last_meal, NULL);
	my_usleep(philos[i].options->time_to_eat);
	philos[i].meals_nb++;
	pthread_mutex_unlock(&table->mutex[philos[i].l_fork - 1]);
	pthread_mutex_unlock(&table->mutex[philos[i].r_fork - 1]);
//	if (*table->all_alive == TRUE)
//		printf("%.5ld %d is sleeping\n",
//				get_timestamp(table->start), philos[i].id);
	print_status(SLEEPING, table, philos, i);
	my_usleep(philos[i].options->time_to_sleep);
//	if (*table->all_alive == TRUE)
//		printf("%.5ld %d is thinking\n",
//				get_timestamp(table->start), philos[i].id);
	print_status(THINKING, table, philos, i);
}

int	grab_fork(t_arg *table, t_philo *philos, int i)
{
	if (i % 2 == 0)
	{
		if (pthread_mutex_lock(&table->mutex[philos[i].r_fork - 1]) != 0)
			return (-1);
//		if (*table->all_alive == TRUE)
//			printf("%.5ld %d has taken a fork\n",
//					get_timestamp(table->start), philos[i].id);
		print_status(FORK, table, philos, i);
	}
	if (pthread_mutex_lock(&table->mutex[philos[i].l_fork - 1]) != 0)
		return (-1);
//	if (*table->all_alive == TRUE)
//		printf("%.5ld %d has taken a fork\n", 
//				get_timestamp(table->start), philos[i].id);
	print_status(FORK, table, philos, i);
	if (i % 2 == 1)
	{
		if (pthread_mutex_lock(&table->mutex[philos[i].r_fork - 1]) != 0)
			return (-1);
//		if (*table->all_alive == TRUE)
//			printf("%.5ld %d has taken a fork\n",
//					get_timestamp(table->start), philos[i].id);
		print_status(FORK, table, philos, i);
	}
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
//	while (*table->all_alive == TRUE)
	{
		if (philos->options->extra_nb > 0 && j >= philos->options->extra_nb)
			break;
		if (grab_fork(table, philos, i) == 0)
			start_eating(table, philos, i);
		j++;
	}
	return (NULL);
}
