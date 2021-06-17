/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarboul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 08:05:33 by mlarboul          #+#    #+#             */
/*   Updated: 2021/06/17 14:44:05 by mlarboul         ###   ########.fr       */
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

void	*routine(void *arg)
{
	t_arg		*table;
	t_philo		*philos;
	int			i;

	table = (t_arg *)arg;
	i = table->i;
	philos = table->philos;
	while (table->all_alive)
	{
		printf("I'm stuck here, BITCH 0\n");
		while (pthread_mutex_lock(&table->mutex[philos[i].l_fork - 1]) != 0)
			printf("I'm stuck here, BITCH 1\n");
		printf("I'm stuck here, BITCH 10\n");
		while (pthread_mutex_lock(&table->mutex[philos[i].r_fork - 1]) != 0)
			printf("I'm stuck here, BITCH 2\n");
		printf("%.5ld %d has taken a left fork\n", get_timestamp(table->start), philos[i].id);
		printf("%.5ld %d has taken a right fork\n", get_timestamp(table->start), philos[i].id);
		printf("%.5ld %d is eating\n", get_timestamp(table->start), philos[i].id);
//		my_usleep(philos[i].options->time_to_eat);
		my_usleep(44);
		pthread_mutex_unlock(&table->mutex[philos[i].l_fork - 1]);
		pthread_mutex_unlock(&table->mutex[philos[i].r_fork - 1]);
		printf("%.5ld %d is sleeping\n", get_timestamp(table->start), philos[i].id);
		my_usleep(255);
//		my_usleep(philos[i].options->time_to_sleep);
		printf("%.5ld %d is thinking\n", get_timestamp(table->start), philos[i].id);
	}
	return (NULL);
}
