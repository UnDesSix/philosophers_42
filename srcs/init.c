/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarboul <mlarboul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 19:30:43 by mlarboul          #+#    #+#             */
/*   Updated: 2021/06/26 10:20:35 by mlarboul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	init_mtx(t_mtx *mtx, int philo_nb)
{
	int	i;

	i = -1;
	while (++i < philo_nb)
		if (pthread_mutex_init(&mtx->fork[i], NULL) != 0)
			return (-1);
	if (pthread_mutex_init(&mtx->display, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&mtx->alive, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&mtx->meals, NULL) != 0)
		return (-1);
	return (0);
}

t_mtx	*create_mtx(t_opt *options)
{
	t_mtx	*mtx;

	mtx = malloc(sizeof(t_mtx));
	if (mtx == NULL)
		return (NULL);
	mtx->fork = malloc(sizeof(pthread_mutex_t) * options->philo_nb);
	if (mtx->fork == NULL)
		return (NULL);
	if (init_mtx(mtx, options->philo_nb) != 0)
		return (NULL);
	return (mtx);
}

int	init_arg(t_arg *arg, t_philo *philos, t_mtx *mtx, int philo_nb)
{
	int				i;
	t_bool			*all_alive;
	struct timeval	start;

	all_alive = malloc(sizeof(t_bool));
	if (all_alive == NULL)
		return (-1);
	*all_alive = TRUE;
	i = -1;
	while (++i < philo_nb)
	{
		arg[i].i = i;
		arg[i].mtx = mtx;
		arg[i].all_alive = all_alive;
		arg[i].philos = philos;
	}
	i = -1;
	if (gettimeofday(&start, NULL) != 0)
		return (-1);
	while (++i < philo_nb)
		arg[i].start = start;
	return (0);
}

t_arg	*create_arg(t_opt *options)
{
	t_arg	*arg;
	t_mtx	*mtx;
	t_philo	*philos;

	arg = malloc(sizeof(t_arg) * options->philo_nb);
	if (arg == NULL)
		return (NULL);
	philos = set_table(options);
	if (philos == NULL)
		return (NULL);
	mtx = create_mtx(options);
	if (mtx == NULL)
		return (NULL);
	if (init_arg(arg, philos, mtx, options->philo_nb) != 0)
		return (NULL);
	return (arg);
}
