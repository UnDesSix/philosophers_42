/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarboul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 07:10:29 by mlarboul          #+#    #+#             */
/*   Updated: 2021/06/21 08:12:45 by mlarboul         ###   ########.fr       */
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
	int			philo_nb;
	suseconds_t	time_to_die;
	suseconds_t	time_to_eat;
	suseconds_t	time_to_sleep;
	int			extra_nb;
}				t_opt;

typedef struct	s_philo
{
	t_opt			*options;
	pthread_t		th;
	int				id;
	struct timeval	last_meal;
	int				meals_nb;
	int				l_fork;
	int				r_fork;
}				t_philo;

typedef struct	s_arg
{
	t_philo			*philos;
	pthread_mutex_t	*mutex;
	int				i;
	t_bool			*all_alive;
	struct timeval	start;
	
}				t_arg;

/*
**	CHECK_ARGS
*/

t_bool	valid_arg(int argc, char **argv);

/*
**	UTILS
*/

int		ft_atoi(const char *str);
int		arg_is_wrong(int arg_nb, int err_code);

/*
**	SAVE_OPTIONS
*/
t_bool	wrong_options(t_opt *options);
t_opt	*save_options(int argc, char **argv);

/*
**	CREATE_PHILO
*/

int		create_philo(t_opt *options, t_arg *arg);
t_arg	*init_arg(t_opt *options);
/*
**	ROUTINE
*/
void	*routine(void *arg);

/*
**	TIME
*/

int		my_usleep(suseconds_t usec);
long	get_timestamp(struct timeval begin);

#endif
