/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   time.c                                            :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/10/19 01:09:10 by sreerink      #+#    #+#                 */
/*   Updated: 2024/10/19 01:25:53 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

un_long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
