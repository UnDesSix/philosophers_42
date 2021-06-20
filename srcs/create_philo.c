/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarboul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 10:57:56 by mlarboul          #+#    #+#             */
/*   Updated: 2021/06/20 10:37:32 by mlarboul         ###   ########.fr       */
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
	if (arg->all_alive)
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

t_arg	*init_arg(t_opt *options)
{
	t_arg			*arg;
	t_philo			*philos;
	pthread_mutex_t	*mutex;
	struct timeval	start;
	int				i;
	t_bool			*all_alive;

	arg = malloc(sizeof(t_arg) * options->philo_nb);
	if (arg == NULL)
		return (NULL);
	philos = set_table(options);
	if (philos == NULL)
		return (NULL);
	mutex = malloc(sizeof(pthread_mutex_t) * options->philo_nb);
	if (mutex == NULL)
		return (NULL);
	all_alive = malloc(sizeof(t_bool));
	if (all_alive == NULL)
		return (NULL);
	*all_alive = TRUE;
	i = -1;
	gettimeofday(&start, NULL);
	while (++i < options->philo_nb)
	{
		arg[i].philos = philos;
		arg[i].i = i;
		arg[i].mutex = mutex;
		arg[i].start = start;
		arg[i].all_alive = all_alive;
		pthread_mutex_init(&mutex[i], NULL);
	}
	return (arg);
}

t_bool	everyone_ate(t_arg *arg, t_opt *options)
{
	int	i;

	i = 0;
	while (i < options->philo_nb)
	{
		if (options->extra_nb > arg->philos[i].meals_nb)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

t_bool	end_conditions(t_arg *arg, t_opt *options)
{
	int	i;

	i = 0;
	if (options->extra_nb >= 0 && everyone_ate(arg, options) == TRUE)
	{
		*arg->all_alive = FALSE;
		return (TRUE);
	}
	while (i < options->philo_nb)
	{
		if (get_timestamp(arg->philos[i].last_meal) >
				options->time_to_die)
		{
			*arg->all_alive = FALSE;
			printf("%.5ld %d died\n",
					get_timestamp(arg->start), arg->philos[i].id);
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
	int		already_died;


	arg = init_arg(options);
	if (arg == NULL)
		return (-1);
	i = -1;
	already_died = FALSE;
	while (++i < options->philo_nb)
	{
		if (pthread_create(&arg[i].philos[i].th, NULL, &routine, &arg[i]) != 0)
			return (-1);
		if (*arg->all_alive == TRUE && end_conditions(arg, options) == TRUE)
		{
			options->philo_nb = i;
			already_died = TRUE;
			break ;
		}
	}
	while (already_died == FALSE && end_conditions(arg, options) == FALSE)
	{
		usleep(100);
	}
	i = -1;
	while (++i < options->philo_nb)
		pthread_detach(arg[i].philos[i].th);
//			return (-1);
	free_all(arg);
	return (0);
}
