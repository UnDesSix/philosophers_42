/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarboul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 10:57:56 by mlarboul          #+#    #+#             */
/*   Updated: 2021/06/09 11:37:20 by mlarboul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	create_philo(t_opt *options)
{
	pthread_t	*th;
	int			i;

	i = 0;
	th = malloc(sizeof(pthread_t) * options->philo_nb);
	if (th == NULL)
		return (-1);
	while (i++ < options->philo_nb)
		pthread_create(&th[i], NULL, &routine, NULL);
	i = 0
	while (i++ < options->philo_nb)
		pthread_join(th[i], NULL);
	return (0);
}
