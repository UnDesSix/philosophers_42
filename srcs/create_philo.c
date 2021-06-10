/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarboul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 10:57:56 by mlarboul          #+#    #+#             */
/*   Updated: 2021/06/10 09:55:07 by mlarboul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*routine(void *arg)
{
	t_philo	*philos;

	philos = (t_philo *)arg;
	printf("I there, I'm philosopher %d.\n", philos->id);
	return (NULL);
}

t_philo	*set_table(t_opt *options)
{
	int		i;
	t_philo	*philos;

	i = 0;
	philos = malloc(sizeof(t_philo) * options->philo_nb);
	if (philos == NULL)
		return (NULL);
	while (i < options->philo_nb)
	{
		philos[i].options = options;
		philos[i].name = i + 1;
		philos[i].fork = i + 1;
		i++;
	}
	return (philos);
}

int	create_philo(t_opt *options)
{
	int		i;
	t_philo	*philos;

	i = -1;
	philos = set_table(options);
	if (philos == NULL)
		return (-1);
	while (++i < options->philo_nb)
	{
		philos[i].name = i + 1;
		pthread_create(&philos[i].th, NULL, &routine, &philos[i]);
	}
	i = -1;
	while (++i < options->philo_nb)
		pthread_join(philos[i].th, NULL);
	if (philos != NULL)
		free(philos);
	return (0);
}
