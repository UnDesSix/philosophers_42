/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarboul <mlarboul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 11:23:44 by mlarboul          #+#    #+#             */
/*   Updated: 2021/06/25 17:04:10 by mlarboul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long int	get_time(void)
{
	struct timeval	tmp;

	gettimeofday(&tmp, NULL);
	return (tmp.tv_sec * 1000 + tmp.tv_usec / 1000);
}

int	my_usleep(long int ms, t_arg *table)
{
	long int	curr;
	long int	end;

	curr = get_time();
	end = curr + ms;
	while (get_time() < end && is_alive(table) == TRUE)
		usleep(100);
	return (0);
}

long	get_timestamp(struct timeval begin)
{
	long			start;
	long			end;
	struct timeval	current;

	start = begin.tv_sec * 1000 + begin.tv_usec / 1000;
	gettimeofday(&current, NULL);
	end = current.tv_sec * 1000 + current.tv_usec / 1000;
	return ((end - start));
}
