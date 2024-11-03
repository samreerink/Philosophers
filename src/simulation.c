/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   simulation.c                                      :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/10/27 16:16:55 by sreerink      #+#    #+#                 */
/*   Updated: 2024/11/03 21:42:00 by sreerink      ########   odam.nl         */
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

void	*dinner_start(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_sync_threads(philo);
	while (!simulation_finished(philo->table))
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

static bool	start_philo_threads(t_table *table)
{
	int	i;

	i = 0;
	if (table->philo_n == 1)
	{
		if (pthread_create(&table->philos[0].philo_thread, NULL, \
					solo_philo, &table->philos[0]) != 0)
		{
			// error msg, perror is temp;
			perror("philo");
			return (false);
		}
		return (true);
	}
	while (i < table->philo_n)
	{
		if (pthread_create(&table->philos[i].philo_thread, NULL, \
					dinner_start, &table->philos[i]) != 0)
		{
			// error msg, perror is temp;
			perror("philo");
			return (false);
		}
		i++;
	}
	return (true);
}

static bool	join_philo_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_n)
	{
		if (pthread_join(table->philos[i].philo_thread, NULL) != 0)
		{
			// error msg, perror is temp;
			perror("philo");
			return (false);
		}
		i++;
	}
	return (true);
}

int	philo_simulation(t_table *table)
{
	if (table->max_nbr_eat == 0)
		return (0);
	else
	{
		if (!start_philo_threads(table))
			return (1);
		pthread_create(&table->monitor_thread, NULL, monitor, table);
		table->philo_start_time = get_time();
		safe_set_bool(&table->table_mutex, &table->threads_ready, true);
		join_philo_threads(table);
		pthread_join(table->monitor_thread, NULL);
	}
	return (0);
}
