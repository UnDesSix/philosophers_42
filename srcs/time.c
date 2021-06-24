/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarboul <mlarboul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 11:23:44 by mlarboul          #+#    #+#             */
/*   Updated: 2021/06/24 08:30:37 by mlarboul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

suseconds_t	get_time(void)
{
	struct timeval	tmp;
	suseconds_t		microseconds;

	gettimeofday(&tmp, NULL);
	microseconds = tmp.tv_sec * 1E6;
	microseconds += tmp.tv_usec;
	return (microseconds);
}

int	my_usleep(suseconds_t ms, t_arg *table)
{
	suseconds_t	curr;
	suseconds_t	end;

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

