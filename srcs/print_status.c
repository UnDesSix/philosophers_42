/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarboul <mlarboul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 11:22:18 by mlarboul          #+#    #+#             */
/*   Updated: 2021/06/24 11:03:36 by mlarboul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"


t_bool	is_alive(t_arg *table)
{
	pthread_mutex_lock(table->alive_mtx); 
	if (*table->all_alive == TRUE)
	{
		pthread_mutex_unlock(table->alive_mtx); 
		return (TRUE);
	}
	pthread_mutex_unlock(table->alive_mtx); 
	return (FALSE);
}

void	print_status(int status, t_arg *table, t_philo *philos, int i)
{
	pthread_mutex_lock(table->display_mtx);
	if (status == EATING && is_alive(table) == TRUE)
		printf("%.5ld %d is eating\n",
				get_timestamp(table->start), philos[i].id);
	else if (status == SLEEPING && is_alive(table) == TRUE)
		printf("%.5ld %d is sleeping\n",
				get_timestamp(table->start), philos[i].id);
	else if (status == THINKING && is_alive(table) == TRUE)
		printf("%.5ld %d is thinking\n",
				get_timestamp(table->start), philos[i].id);
	else if (status == FORK && is_alive(table) == TRUE)
		printf("%.5ld %d has taken a fork\n",
				get_timestamp(table->start), philos[i].id);
	pthread_mutex_unlock(table->display_mtx);
}
