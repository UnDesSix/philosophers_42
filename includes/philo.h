/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarboul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 07:10:29 by mlarboul          #+#    #+#             */
/*   Updated: 2021/06/09 11:37:24 by mlarboul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

# define FALSE 0
# define TRUE 1

typedef int	t_bool;

typedef struct	s_opt
{
	int	philo_nb;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	extra_nb;
}				t_opt;

/*
**	CHECK_ARGS
*/

t_bool	valid_arg(int argc, char **argv);

/*
**	UTILS
*/

int	ft_atoi(const char *str);
int	arg_is_wrong(int arg_nb, int err_code);

/*
**	SAVE_OPTIONS
*/

t_opt	*save_options(int argc, char **argv)

#endif
