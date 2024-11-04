/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   threads.c                                         :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/11/04 18:05:12 by sreerink      #+#    #+#                 */
/*   Updated: 2024/11/04 19:39:33 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	wait_sync_threads(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	while (!safe_get_bool(&table->table_mutex, &table->threads_ready))
		;
	if (table->philo_n % 2 == 0)
	{
		if (philo->philo_id % 2 == 0)
			improved_usleep(3, table);
	}
}

bool	start_philo_threads(t_table *table)
{
	int	i;

	i = 0;
	if (table->philo_n == 1)
	{
		if (pthread_create(&table->philos[0].philo_thread, NULL, \
					solo_philo, &table->philos[0]) != 0)
		{
			write(STDERR_FILENO, "philo: pthread_create() failed\n", 31);
			return (false);
		}
		return (true);
	}
	while (i < table->philo_n)
	{
		if (pthread_create(&table->philos[i].philo_thread, NULL, \
					dinner_start, &table->philos[i]) != 0)
		{
			join_philo_threads(table, i);
			write(STDERR_FILENO, "philo: pthread_create() failed\n", 31);
			return (false);
		}
		i++;
	}
	return (true);
}

void	join_philo_threads(t_table *table, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		pthread_join(table->philos[i].philo_thread, NULL);
		i++;
	}
}
