/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   main.c                                            :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/10/14 23:48:10 by sreerink      #+#    #+#                 */
/*   Updated: 2024/10/15 05:21:25 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int argc, char *argv[])
{
	t_table	table;

	if (argc != 5 && argc != 6)
		return (error_philo("program requires 4 or 5 arguments", NULL));
	if (parse_input(argv, &table) == 1)
		return (error_philo("one or more inputs are invalid", NULL));
	return (0);
}
