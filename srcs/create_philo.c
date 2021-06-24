/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarboul <mlarboul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 11:23:04 by mlarboul          #+#    #+#             */
/*   Updated: 2021/06/24 12:16:16 by mlarboul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	free_all(t_arg *arg)
{
	int	i;

	i = -1;
	//	while (++i < arg->philos->options->philo_nb)
	//		pthread_mutex_destroy(&arg->mutex[i]);

	pthread_mutex_destroy(arg->display_mtx);
	free(arg->display_mtx);
	free(arg->alive_mtx);
	if (arg->philos != NULL)
		free(arg->philos);
	if (arg->mutex != NULL)
		free(arg->mutex);
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

t_arg	*init_arg(t_opt *options)
{
	t_arg			*arg;
	t_philo			*philos;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	*display_mtx;
	pthread_mutex_t	*alive_mtx;
	pthread_mutex_t	*meals_mtx;
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
	display_mtx = malloc(sizeof(pthread_mutex_t));
	if (display_mtx == NULL)
		return (NULL);
	alive_mtx = malloc(sizeof(pthread_mutex_t));
	if (alive_mtx == NULL)
		return (NULL);
	meals_mtx = malloc(sizeof(pthread_mutex_t));
	if (meals_mtx == NULL)
		return (NULL);
	all_alive = malloc(sizeof(t_bool));
	if (all_alive == NULL)
		return (NULL);
	i = -1;
	gettimeofday(&start, NULL);
	while (++i < options->philo_nb)
	{
		arg[i].philos = philos;
		arg[i].i = i;
		arg[i].mutex = mutex;
		arg[i].display_mtx = display_mtx;
		arg[i].alive_mtx = alive_mtx;
		arg[i].meals_mtx = alive_mtx;
		arg[i].start = start;
		arg[i].all_alive = all_alive;
		pthread_mutex_init(&mutex[i], NULL);
	}
	pthread_mutex_init(arg->display_mtx, NULL);
	pthread_mutex_init(arg->alive_mtx, NULL);
	*all_alive = TRUE;
	return (arg);
}

t_bool	everyone_ate(t_arg *arg, t_opt *options)
{
	int	i;

	i = 0;
	while (i < options->philo_nb)
	{
		pthread_mutex_lock(arg->meals_mtx);
		if (options->extra_nb > arg->philos[i].meals_nb)
		{
			pthread_mutex_unlock(arg->meals_mtx);
			return (FALSE);
		}
		pthread_mutex_unlock(arg->meals_mtx);
		i++;
	}
	return (TRUE);
}

t_bool	end_conditions(t_arg *arg, t_opt *options)
{
	int	i;

	i = 0;
	while (i < options->philo_nb)
	{
		if (options->extra_nb >= 0 && everyone_ate(arg, options) == TRUE)
		{
			pthread_mutex_lock(arg->alive_mtx);
			*arg->all_alive = FALSE;
			pthread_mutex_unlock(arg->alive_mtx);
			pthread_mutex_lock(arg->display_mtx);
			printf("Everyone ate enough\n");
			pthread_mutex_unlock(arg->display_mtx);
			return (TRUE);
		}
		if (get_timestamp(arg->philos[i].last_meal) >
				options->time_to_die)
		{
			pthread_mutex_lock(arg->alive_mtx);
			*arg->all_alive = FALSE;
			pthread_mutex_unlock(arg->alive_mtx);
			pthread_mutex_lock(arg->display_mtx);
			printf("%.5ld %d died\n",
					get_timestamp(arg->start), arg->philos[i].id);
			pthread_mutex_unlock(arg->display_mtx);
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
	i = 0;
	while (i < options->philo_nb)
	{
		if (pthread_create(&arg[i].philos[i].th, NULL, &routine, &arg[i]) != 0)
			return (-1);
		i += 2;
	}
	my_usleep(10, arg);
	i = 1;
	while (i < options->philo_nb)
	{
		if (pthread_create(&arg[i].philos[i].th, NULL, &routine, &arg[i]) != 0)
			return (-1);
		i += 2;
	}
	while (end_conditions(arg, options) == FALSE)
		usleep(100);
	i = -1;
	while (++i < options->philo_nb)
		pthread_join(arg[i].philos[i].th, NULL);
	//			return (-1);
	free_all(arg);
	return (0);
}
