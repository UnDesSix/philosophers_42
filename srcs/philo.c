/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarboul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 07:09:40 by mlarboul          #+#    #+#             */
/*   Updated: 2021/06/09 10:49:06 by mlarboul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	check_opt_values(t_opt *options)
{
	printf("philo_nb : %d\n", options->philo_nb);
	printf("time to eat : %d\n", options->time_to_die);
	printf("time to die: %d\n", options->time_to_eat);
	printf("time to sleep : %d\n", options->time_to_sleep);
	printf("extra nb : %d\n", options->extra_nb);
}

int	main(int argc, char **argv)
{
	t_opt	*options;

	if (valid_arg(argc, argv) == FALSE)
		return (0);
	options = save_options(argc, argv);
	check_opt_values(options);
	free(options);
	return (0);
}
