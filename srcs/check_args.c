/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarboul <mlarboul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 11:22:53 by mlarboul          #+#    #+#             */
/*   Updated: 2021/06/23 11:22:57 by mlarboul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_bool	valid_arg(int argc, char **argv)
{
	int	i;
	int	valid;

	i = 0;
	valid = TRUE;
	if (argc < 5 || argc > 6)
	{
		printf("Error - Wrong numbers of arguments.\n");
		return (FALSE);
	}
	while (++i < argc)
		if (arg_is_wrong(i, ft_atoi(argv[i])) == TRUE)
			valid = FALSE;
	if (valid == FALSE)
		return (FALSE);
	return (TRUE);
}
