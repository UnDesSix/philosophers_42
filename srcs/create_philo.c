/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarboul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 10:57:56 by mlarboul          #+#    #+#             */
/*   Updated: 2021/06/19 11:55:10 by mlarboul         ###   ########.fr       */
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
		gettimeofday(&philos[i].last_meal, NULL);
		philos[i].meals_nb = 0;
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
	t_bool			all_alive;

	arg = malloc(sizeof(t_arg) * options->philo_nb);
	if (arg == NULL)
		return (NULL);
	philos = set_table(options);
	if (philos == NULL)
		return (NULL);
	mutex = malloc(sizeof(pthread_mutex_t) * options->philo_nb);
	if (mutex == NULL)
		return (NULL);
	all_alive = TRUE;
	i = -1;
	gettimeofday(&start, NULL);
	while (++i < options->philo_nb)
	{
		arg[i].philos = philos;
		arg[i].i = i;
		arg[i].mutex = mutex;
		arg[i].start = start;
		arg[i].all_alive = &all_alive;
		pthread_mutex_init(&mutex[i], NULL);
	}
	return (arg);
}

t_bool	end_conditions(t_arg *arg, t_opt *options)
{
	int	i;

	usleep(5000);
	i = 0;
	while (i < options->philo_nb)
	{
		if (get_timestamp(arg->philos[i].last_meal)
				> options->time_to_die * 1E3)
		{
			*arg->all_alive = FALSE;
			printf("%.5ld %d DIEED\n\n\n\n",
					(long)(get_timestamp(arg->start) / 1E3), arg->philos[i].id);
			return (TRUE);
		}
		if (options->extra_nb >= 0 &&
				options->extra_nb <= arg->philos[i].meals_nb)
		{
			*arg->all_alive = FALSE;
			printf("%.5ld %d died\n",
					(long)(get_timestamp(arg->start) / 1E3), arg->philos[i].id);
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
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
	while (end_conditions(arg, options) == FALSE)
		;
//	i = -1;
//	while (++i < options->philo_nb)
//		if (pthread_join(arg[i].philos[i].th, NULL) != 0)
//			return (-1);
	free_all(arg);
	return (0);
}
