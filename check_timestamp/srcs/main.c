/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarboul <mlarboul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 15:22:30 by mlarboul          #+#    #+#             */
/*   Updated: 2021/06/23 16:21:18 by mlarboul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/check_timestamp.h"

static int	ft_is_space(char c)
{
	if (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	result;

	i = 0;
	sign = 1;
	result = 0;
	while (ft_is_space(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			sign *= -1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - 48;
		i++;
	}
	return (result * sign);
}

int	checker(char **argv)
{
	char	*line;
	int		i;
	int		fd;
	int		value[2];

	i = 1;
	value[0] = 0;
	value[1] = 1;
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (-1);
	while (get_next_line(fd, &line))
	{
		value[1] = ft_atoi(line);
		if (value[0] > value[1])
		{
			printf("line[%d] : %d is bigger than %d.. That's weird\n",
				i - 1, value[0], value[1]);
			return (2);
		}
		value[0] = value[1];
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	int value;

	if (argc != 2)
	{
		printf("Please give me juste one argument : file you want to check.\n");
		return (0);
	}
	value = checker(argv);
	printf("value : %d\n", value);
	if (value == 0)	
		printf("OK.\n");
	else
		printf("KO.\n");
	return (0);
}

