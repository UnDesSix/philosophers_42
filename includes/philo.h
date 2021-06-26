/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarboul <mlarboul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 11:25:22 by mlarboul          #+#    #+#             */
/*   Updated: 2021/06/26 10:33:54 by mlarboul         ###   ########.fr       */
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

# define EATING 0
# define SLEEPING 1
# define THINKING 2
# define FORK 3
# define DEAD 4
# define ALL_ATE 5

typedef int	t_bool;

typedef struct s_mtx
{
	pthread_mutex_t	*fork;
	pthread_mutex_t	display;
	pthread_mutex_t	alive;
	pthread_mutex_t	meals;
}				t_mtx;

typedef struct s_opt
{
	int			philo_nb;
	long int	time_to_die;
	long int	time_to_eat;
	long int	time_to_sleep;
	int			extra_nb;
}				t_opt;

typedef struct s_philo
{
	t_opt			*options;
	pthread_t		th;
	int				id;
	struct timeval	last_meal;
	int				meals_nb;
	int				l_fork;
	int				r_fork;
}				t_philo;

typedef struct s_arg
{
	int				i;
	t_mtx			*mtx;
	t_bool			*all_alive;
	t_philo			*philos;
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

int		create_philo(t_opt *options);
t_philo	*set_table(t_opt *options);
t_arg	*create_arg(t_opt *options);

/*
**	ROUTINE
*/
t_bool	end_conditions(t_arg *arg, t_opt *options, t_philo *philos);
void	*routine(void *arg);

/*
**	TIME
*/

int		my_usleep(long int usec, t_arg *table);
long	get_timestamp(struct timeval begin);

/*
**	TIME
*/
void	print_status(int status, t_arg *table, t_philo *philos, int i);
t_bool	is_alive(t_arg *table);

#endif
