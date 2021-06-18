/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarboul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 08:05:33 by mlarboul          #+#    #+#             */
/*   Updated: 2021/06/18 10:11:41 by mlarboul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	my_usleep(suseconds_t usec)
{
	struct timeval	obj_time;
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	obj_time.tv_usec = current_time.tv_sec * 1E6 + current_time.tv_usec + usec;
	while (current_time.tv_sec * 1E6 + current_time.tv_usec < obj_time.tv_usec)
	{
		gettimeofday(&current_time, NULL);
	}
	return (0);
}

long	get_timestamp(struct timeval begin)
{
	long		start;
	long		end;
	struct timeval	current;

	start = begin.tv_sec * 1E6 + begin.tv_usec;
	gettimeofday(&current, NULL);
	end = current.tv_sec * 1E6 + current.tv_usec;
	return ((end - start) / 1E3);
}

int	grab_fork(t_arg *table, t_philo *philos, int i)
{
//	int	left_fork_res;
//	int	right_fork_res;

/*	if (i % 2 == 0)
		right_fork_res = pthread_mutex_lock(&table->mutex[philos[i].r_fork - 1]);
	left_fork_res = pthread_mutex_lock(&table->mutex[philos[i].l_fork - 1]);
	if (i % 2 == 1)
		right_fork_res = pthread_mutex_lock(&table->mutex[philos[i].r_fork - 1]);
	if (left_fork_res == 0 && right_fork_res == 0)
		return (0);
	else if (left_fork_res == 0 && right_fork_res != 0)
	{
		pthread_mutex_unlock(&table->mutex[philos[i].l_fork - 1]);
		grab_fork(table, philos, i);
	}
	else if (left_fork_res != 0 && right_fork_res == 0)
	{
		pthread_mutex_unlock(&table->mutex[philos[i].r_fork - 1]);
		grab_fork(table, philos, i);
	}
	else
		grab_fork(table, philos, i);
*/
	if (i % 2 == 0)
		while (pthread_mutex_lock(&table->mutex[philos[i].r_fork - 1]))
			;
	while (pthread_mutex_lock(&table->mutex[philos[i].l_fork - 1]))
		;
	if (i % 2 == 1)
		while (pthread_mutex_lock(&table->mutex[philos[i].r_fork - 1]))
			;
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
	while (1)
	{
		grab_fork(table, philos, i);
		printf("%.5ld %d has taken a left fork\n", get_timestamp(table->start), philos[i].id);
		printf("%.5ld %d has taken a right fork\n", get_timestamp(table->start), philos[i].id);
		printf("%.5ld %d is eating\n", get_timestamp(table->start), philos[i].id);
		my_usleep(philos[i].options->time_to_eat * 1000);
		pthread_mutex_unlock(&table->mutex[philos[i].l_fork - 1]);
		pthread_mutex_unlock(&table->mutex[philos[i].r_fork - 1]);
		printf("%.5ld %d is sleeping\n", get_timestamp(table->start), philos[i].id);
		my_usleep(philos[i].options->time_to_sleep * 1000);
		printf("%.5ld %d is thinking\n", get_timestamp(table->start), philos[i].id);
	}
	return (NULL);
}
