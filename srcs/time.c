/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarboul <mlarboul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 11:23:44 by mlarboul          #+#    #+#             */
/*   Updated: 2021/06/23 11:23:46 by mlarboul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

suseconds_t	get_time(void)
{
	struct timeval	tmp;
	suseconds_t		milliseconds;

	gettimeofday(&tmp, NULL);
	milliseconds = tmp.tv_sec * 1000;
	milliseconds += tmp.tv_usec / 1000;
	return (milliseconds);
}

int	my_usleep(suseconds_t ms)
{
	suseconds_t	curr;
	suseconds_t	end;

	curr = get_time();
	end = curr + ms;
	while (get_time() < end)
		usleep(500);
	return (0);
}

/*
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
}*/

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

