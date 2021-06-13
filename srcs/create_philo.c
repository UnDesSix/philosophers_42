/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarboul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 10:57:56 by mlarboul          #+#    #+#             */
/*   Updated: 2021/06/13 12:21:18 by mlarboul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*routine(void *arg)
{
	t_philo	*philos;
	int		i;

	philos = (t_philo *)arg;
	i = philos->current;
	printf("%d - ", i);
	printf("I there, I'm philosopher %d.\n", philos[i].id);
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
		philos[i].id = i + 1;
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
	while (++i < 1)
	{
		philos[0].current = i;
		pthread_create(&philos[i].th, NULL, &routine, philos);
	}
	i = -1;
	while (++i < 1)
		pthread_join(philos[i].th, NULL);
	if (philos != NULL)
		free(philos);
	return (0);
}
