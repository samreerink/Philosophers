/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   time.c                                            :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/10/19 01:09:10 by sreerink      #+#    #+#                 */
/*   Updated: 2024/10/27 11:34:30 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	improved_usleep(int sleep_time, t_table *table)
{
	long	start;
	long	elapsed;
	long	rem_usec;

	start = get_time();
	while (get_time() - start < sleep_time)
	{
		if (simulation_finished(table))
			return ;
		elapsed = get_time() - start;
		rem_usec = (sleep_time - elapsed) * 1000;
		if (rem_usec > 1000)
			usleep(rem_usec / 2);
		else
		{
			while (get_time() - start < sleep_time)
				;
		}
	}
}
