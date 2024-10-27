/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   parsing.c                                         :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/10/15 01:46:41 by sreerink      #+#    #+#                 */
/*   Updated: 2024/10/27 16:06:33 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static char	*check_valid_input(char *str)
{
	size_t	i;

	i = 0;
	while (is_whitespace(str[i]))
		i++;
	if (str[i] == '+')
		i++;
	if (!is_digit(str[i]))
		return (NULL);
	if (ft_strlen(str + i) > 10)
		return (NULL);
	return (str + i);
}

static long	ft_atol(char *str)
{
	size_t	i;
	long	num;

	i = 0;
	num = 0;
	str = check_valid_input(str);
	if (!str)
		return (-1);
	while (is_digit(str[i]))
	{
		num = (num * 10) + (str[i] - 48);
		i++;
	}
	if (num > INT_MAX)
		return (-1);
	return (num);
}

int	parse_input(char **argv, t_table *table)
{
	table->philo_n = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]);
	table->time_to_eat = ft_atol(argv[3]);
	table->time_to_sleep = ft_atol(argv[4]);
	if (argv[5])
		table->max_nbr_eat = ft_atol(argv[5]);
	else
		table->max_nbr_eat = -2;
	if (table->philo_n == -1 || table->time_to_die == -1 || \
		table->time_to_eat == -1 || table->time_to_sleep == -1 || \
		table->max_nbr_eat == -1)
		return (1);
	return (0);
}
