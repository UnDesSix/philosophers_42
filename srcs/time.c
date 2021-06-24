/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarboul <mlarboul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 11:23:44 by mlarboul          #+#    #+#             */
/*   Updated: 2021/06/24 19:34:27 by mlarboul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long int	get_time(void)
{
	struct timeval	tmp;
	long int		microseconds;

	gettimeofday(&tmp, NULL);
	microseconds = tmp.tv_sec * 1E6;
	microseconds += tmp.tv_usec;
	return (microseconds);
}

int	my_usleep(long int ms, t_arg *table)
{
	long int	curr;
	long int	end;

	curr = get_time();
	end = curr + ms * 1E3;
	while (get_time() < end && is_alive(table) == TRUE)
		usleep(100);
	return (0);
}

long	get_timestamp(struct timeval begin)
{
	long			start;
	long			end;
	struct timeval	current;

	start = begin.tv_sec * 1E6 + begin.tv_usec;
	gettimeofday(&current, NULL);
	end = current.tv_sec * 1E6 + current.tv_usec;
	return ((end - start) / 1E3);
}
