/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarboul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 07:26:46 by mlarboul          #+#    #+#             */
/*   Updated: 2021/06/09 08:30:44 by mlarboul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	arg_is_wrong(int arg_nb, int err_code)
{
	if (err_code >= 0)
		return (FALSE);
	if (err_code == -1 || err_code == -2)
		printf("Arg %d : Error - Only positive integer are accepted.\n",
			arg_nb);
	if (err_code == -3)
		printf("Arg %d : Error - Value is too high.\n", arg_nb);
	return (TRUE);
}

int	ft_atoi(const char *str)
{
	int		i;
	long	result;

	i = 0;
	result = 0;
	if (!(str[i] >= '0' && str[i] <= '9'))
		return (-1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - 48;
		i++;
	}
	if (str[i] != '\0')
		return (-2);
	if (result > 2147483647 || i > 10)
		return (-3);
	return (result);
}
