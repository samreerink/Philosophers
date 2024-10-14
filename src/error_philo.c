/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   error_philo.c                                     :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/10/14 23:56:39 by sreerink      #+#    #+#                 */
/*   Updated: 2024/10/15 00:10:03 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	error_philo(const char *msg, t_table *table)
{
	if (msg)
	{
		write(STDERR_FILENO, "philo: ", 7);
		write(STDERR_FILENO, msg, ft_strlen(msg));
		write(STDERR_FILENO, "\n", 1);
	}
/*	if (table)
		// free table; */
	return (EXIT_FAILURE);
}
