/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_options.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarboul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 10:35:31 by mlarboul          #+#    #+#             */
/*   Updated: 2021/06/09 10:47:28 by mlarboul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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
