/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarboul <mlarboul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 11:23:20 by mlarboul          #+#    #+#             */
/*   Updated: 2021/06/23 11:23:23 by mlarboul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	check_opt_values(t_opt *options)
{
	printf("philo_nb : %d\n", options->philo_nb);
	printf("time to eat : %ld\n", options->time_to_die);
	printf("time to die: %ld\n", options->time_to_eat);
	printf("time to sleep : %ld\n", options->time_to_sleep);
	printf("extra nb : %d\n", options->extra_nb);
}

int	main(int argc, char **argv)
{
	t_opt	*options;

	if (valid_arg(argc, argv) == FALSE)
		return (0);
	options = save_options(argc, argv);
	if (wrong_options(options) == TRUE)
		return (-1);
	create_philo(options);
	if (options != NULL)
		free(options);
	return (0);
}
