/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarboul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 10:57:56 by mlarboul          #+#    #+#             */
/*   Updated: 2021/06/18 10:25:39 by mlarboul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	free_all(t_arg *arg)
{
	int	i;

	i = -1;
	while (++i < arg->philos->options->philo_nb)
		pthread_mutex_destroy(&arg->mutex[i]);
	if (arg->philos != NULL)
		free(arg->philos);
	if (arg->mutex != NULL)
		free(arg->mutex);
	if (arg != NULL)
		free(arg);
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
		if (i < 1)
			philos[i].l_fork = options->philo_nb;
		else
			philos[i].l_fork = i;
		philos[i].r_fork = i + 1;
//		printf("Philos %d must eat with fork %d and %d.\n",
//				philos[i].id, philos[i].l_fork, philos[i].r_fork);
		i++;
	}
	return (philos);
}

t_arg	*init_arg(t_opt *options)
{
	t_arg			*arg;
	t_philo			*philos;
	pthread_mutex_t	*mutex;
	struct timeval	start;
	int				i;

	arg = malloc(sizeof(t_arg) * options->philo_nb);
	if (arg == NULL)
		return (NULL);
	arg->all_alive = TRUE;
	philos = set_table(options);
	if (philos == NULL)
		return (NULL);
	mutex = malloc(sizeof(pthread_mutex_t) * options->philo_nb);
	if (mutex == NULL)
		return (NULL);
	i = -1;
	gettimeofday(&start, NULL);
	while (++i < options->philo_nb)
	{
		arg[i].philos = philos;
		arg[i].i = i;
		arg[i].mutex = mutex;
		arg[i].start = start;
		pthread_mutex_init(&mutex[i], NULL);
	}
	return (arg);
}

int	create_philo(t_opt *options)
{
	t_arg	*arg;
	int		i;

	arg = init_arg(options);
	if (arg == NULL)
		return (-1);
	i = -1;
	while (++i < options->philo_nb)
		if (pthread_create(&arg[i].philos[i].th, NULL, &routine, &arg[i]) != 0)
			return (-1);
	i = -1;
	while (++i < options->philo_nb)
		if (pthread_join(arg[i].philos[i].th, NULL) != 0)
			return (-1);
	free_all(arg);
	return (0);
}
