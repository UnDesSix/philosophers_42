/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarboul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 10:57:56 by mlarboul          #+#    #+#             */
/*   Updated: 2021/06/16 19:15:42 by mlarboul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*routine(void *arg)
{
	t_arg	*arg_bis;
	int		fork[2];
	t_philo	*philos;
	int		i;

	arg_bis = (t_arg *)arg;
	i = arg_bis->i;
	philos = arg_bis->philos;
	printf("I'm philosopher %.2d, ", philos[i].id);
	if (i + 1 - 1 < 1)
		fork[0] = philos[i].options->philo_nb;
	else
		fork[0] = i + 1 - 1;
	if (i + 1 + 1 > philos[i].options->philo_nb)
		fork[1] = 1;
	else
		fork[1] = i + 1;
	printf("and I can use fork %d and %d to eat.\n", fork[0], fork[1]);
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
	t_arg	*arg;
	t_philo	*tmp;

	i = -1;
	arg = malloc(sizeof(t_arg) * options->philo_nb);
	if (arg == NULL)
		return (-1);
	tmp = set_table(options);
	if (tmp == NULL)
		return (-1);
	while (++i < options->philo_nb)
		arg[i].philos = tmp;
	i = -1;
	while (++i < options->philo_nb)
	{
		arg[i].i = i;
		pthread_create(&arg[i].philos[i].th, NULL, &routine, &arg[i]);
	}
	i = -1;
	while (++i < options->philo_nb)
		pthread_join(arg[i].philos[i].th, NULL);
	if (tmp != NULL)
		free(tmp);
	if (arg != NULL)
		free(arg);
	return (0);
}
