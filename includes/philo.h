/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarboul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 07:10:29 by mlarboul          #+#    #+#             */
/*   Updated: 2021/06/12 09:33:15 by mlarboul         ###   ########.fr       */
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

typedef struct	s_philo
{
	t_opt		*options;
	pthread_t	th;
	int			current;
	int			id;
	int			fork;
}				t_philo;

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
t_bool	wrong_options(t_opt *options);
t_opt	*save_options(int argc, char **argv);

/*
**	CREATE_PHILO
*/

int	create_philo(t_opt *options);

#endif
