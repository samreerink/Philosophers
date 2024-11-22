/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   simulation.c                                      :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/10/27 16:16:55 by sreerink      #+#    #+#                 */
/*   Updated: 2024/11/22 20:19:29 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	wait_sync_threads(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	while (!safe_get_bool(&table->table_mutex, &table->threads_ready))
		;
	if (philo->philo_id % 2 == 0)
		improved_usleep(3, table);
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

int	philo_simulation(t_table *table)
{
	if (table->max_nbr_eat == 0 || table->philo_n == 0)
		return (0);
	else
	{
		if (!start_philo_threads(table))
			return (1);
		pthread_create(&table->monitor_thread, NULL, monitor, table);
		table->philo_start_time = get_time();
		safe_set_bool(&table->table_mutex, &table->threads_ready, true);
		join_philo_threads(table, table->philo_n);
		pthread_join(table->monitor_thread, NULL);
	}
	return (0);
}
