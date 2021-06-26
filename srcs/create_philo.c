/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarboul <mlarboul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 11:23:04 by mlarboul          #+#    #+#             */
/*   Updated: 2021/06/26 10:18:30 by mlarboul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	free_all(t_arg *arg, t_mtx *mtx, int philo_nb)
{
	int	i;

	i = -1;
	while (++i < philo_nb)
		pthread_mutex_destroy(&mtx->fork[i]);
	pthread_mutex_destroy(&mtx->alive);
	pthread_mutex_destroy(&mtx->meals);
	pthread_mutex_destroy(&mtx->display);
	if (mtx->fork != NULL)
		free(mtx->fork);
	if (mtx != NULL)
		free(mtx);
	if (arg->philos != NULL)
		free(arg->philos);
	if (arg->all_alive != NULL)
		free(arg->all_alive);
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
		gettimeofday(&philos[i].last_meal, NULL);
		philos[i].meals_nb = 0;
		i++;
	}
	return (philos);
}

int	create_threads(t_arg *arg, int philo_nb)
{
	int	i;

	i = 0;
	while (i < philo_nb)
	{
		if (pthread_create(&arg[i].philos[i].th, NULL, &routine, &arg[i]) != 0)
			return (-1);
		i += 2;
	}
	usleep(1000);
	i = 1;
	while (i < philo_nb)
	{
		if (pthread_create(&arg[i].philos[i].th, NULL, &routine, &arg[i]) != 0)
			return (-1);
		i += 2;
	}
	return (0);
}

int	create_philo(t_opt *options)
{
	t_arg	*arg;
	int		i;

	arg = create_arg(options);
	if (arg == NULL)
		return (-1);
	if (create_threads(arg, options->philo_nb) != 0)
		return (-1);
	while (end_conditions(arg, options) == FALSE)
		my_usleep(1, arg);
	i = -1;
	while (++i < options->philo_nb)
		pthread_join(arg[i].philos[i].th, NULL);
	free_all(arg, arg->mtx, options->philo_nb);
	return (0);
}
