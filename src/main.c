/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   main.c                                            :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/10/14 23:48:10 by sreerink      #+#    #+#                 */
/*   Updated: 2024/10/15 00:16:41 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int argc, char *argv[])
{
	if (argc != 5 && argc != 6)
		return (error_philo("program requires 4 or 5 arguments", NULL));
	return (EXIT_SUCCESS);
}
