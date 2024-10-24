/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   simulation.c                                      :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/10/18 22:57:57 by sreerink      #+#    #+#                 */
/*   Updated: 2024/10/22 05:04:50 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	wait_sync_threads(t_table *table)
{
	while (!safe_get_bool(&table->table_mutex, &table->threads_ready))
		;
}

void	*dinner_start(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_sync_threads(philo->table);
	while (!simulation_finished(philo->table))
	{
		philo_eat(philo);
		if (philo->max_eaten)
			break ;
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

static bool	philo_threads(t_table *table)
{
	int	i;

	i = 0;
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
	table->philo_start_time = get_time();
	safe_set_bool(&table->table_mutex, &table->threads_ready, true);
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
	safe_set_bool(&table->table_mutex, &table->end_philo_sim, true);
	// pthread join monitor_thread;
	return (true);
}

int	philo_simulation(t_table *table)
{
	if (table->max_nbr_eat == 0)
		return (0);
	else
	{
		if (!philo_threads(table))
			return (1);
	}
	return (0);
}
