/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primes_nb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarboul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 07:20:57 by mlarboul          #+#    #+#             */
/*   Updated: 2021/06/09 07:23:20 by mlarboul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define TH_NB 2

typedef struct	s_arg
{
	int		*value;
	int		i;
	int		*half_sum;
}				t_arg;

void	*routine(void *arg)
{
	t_arg	*final;
	int		total = 0;

	final = (t_arg*)arg;
	for (int i = (final->i) * 5; i < (final->i + 1) * 5; i++)
	{
		printf("%d ", *(final->value + i));
		total += *(final->value + i);
	}
	final->half_sum = malloc(sizeof(int));
	*(final->half_sum) = total;
	return (final->half_sum);
}

int		print_all_primes(void)
{
	int			primes[10] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 };
	pthread_t	th[TH_NB];
	t_arg		*arg;
	int			tot = 0;

	arg = malloc(sizeof(t_arg) * 2);
	for (int i = 0; i < TH_NB; i++)
		arg[i].value = primes;
	for (int i = 0; i < TH_NB; i++)
	{
		arg[i].i = i;
		if (pthread_create(&th[i], NULL, &routine, &(arg[i])) != 0)
			return (-1);
	}
	for (int i = 0; i < TH_NB; i++)
	{
		if (pthread_join(th[i], (void**)&(arg[i].half_sum)) != 0)
			return (-1);
		tot += *(arg[i].half_sum);
		free(arg[i].half_sum);
	}
	printf("\n\nTOTAL = %d\n", tot);
	free(arg);
	return (0);
}

/*
int		main(void)
{
	if (print_all_primes() < 0)
		printf("Error\n");
	return (0);
}*/
