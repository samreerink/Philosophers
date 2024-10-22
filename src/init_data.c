/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   init_data.c                                       :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/10/17 05:12:38 by sreerink      #+#    #+#                 */
/*   Updated: 2024/10/22 04:57:17 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// right_fork = table->forks + i;
// left_fork = table->forks + ((i + 1) % table->philo_n);
static bool	assign_philos(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < table->philo_n)
	{
		philo = table->philos + i;
		philo->philo_id = i + 1;
		if (philo->philo_id % 2 == 0)
		{
			philo->first = table->forks + i;
			philo->second = table->forks + ((i + 1) % table->philo_n);
		}
		else
		{
			philo->first = table->forks + ((i + 1) % table->philo_n);
			philo->second = table->forks + i;
		}
		if (pthread_mutex_init(&philo->philo_mutex, NULL) != 0)
			return (false);
		//printf("Philo #%d: first_fork_id %d, second_fork_id %d\n", philo->philo_id, philo->first->fork_id, philo->second->fork_id);
		philo->table = table;
		i++;
	}
	return (true);
}

int	init_data(t_table *table)
{
	int	i;

	i = 0;
	table->end_philo_sim = false;
	table->philos = ft_calloc(table->philo_n, sizeof(t_philo));
	table->forks = ft_calloc(table->philo_n, sizeof(t_fork));
	if (!table->philos || !table->forks)
		return (1);
	if (pthread_mutex_init(&table->table_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&table->msg_printing, NULL) != 0)
		return (1);
	while (i < table->philo_n)
	{
		if (pthread_mutex_init(&table->forks[i].fork, NULL) != 0)
			return (1);
		table->forks[i].fork_id = i + 1;
		i++;
	}
	if (!assign_philos(table))
		return (1);
	return (0);
}
