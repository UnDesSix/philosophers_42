/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_options.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarboul <mlarboul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 11:23:36 by mlarboul          #+#    #+#             */
/*   Updated: 2021/06/23 11:23:40 by mlarboul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_bool	wrong_options(t_opt *options)
{
	if (options->philo_nb < 1)
	{
		printf("Error - One philosopher at least.\n");
		return (TRUE);
	}
	return (FALSE);
}

t_opt	*save_options(int argc, char **argv)
{
	t_opt	*options;

	options = malloc(sizeof(t_opt));
	if (options == NULL)
		return (NULL);
	options->philo_nb = ft_atoi(argv[1]);
	options->time_to_die = ft_atoi(argv[2]);
	options->time_to_eat = ft_atoi(argv[3]);
	options->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		options->extra_nb = ft_atoi(argv[5]);
	else
		options->extra_nb = -1;
	return (options);
}
