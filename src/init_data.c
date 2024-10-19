/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   init_data.c                                       :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/10/17 05:12:38 by sreerink      #+#    #+#                 */
/*   Updated: 2024/10/18 23:39:55 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	assign_philos(t_table *table)
{
	int				i;
	t_philo			*philo;

	i = 0;
	while (i < table->philo_n)
	{
		philo = table->philos + i;
		philo->philo_id = i + 1;
		philo->right_fork = table->forks + i;
		philo->left_fork = table->forks + ((i + 1) % table->philo_n);
		//printf("Philo #%d: right_fork_id %d, left_fork_id %d\n", philo->philo_id, philo->right_fork->fork_id, philo->left_fork->fork_id);
		philo->table = table;
		i++;
	}
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
	if (pthread_mutex_init(&table->sync_mtx, NULL) != 0)
		return (1);
	while (i < table->philo_n)
	{
		if (pthread_mutex_init(&table->forks[i].fork, NULL) != 0)
			return (1);
		table->forks[i].fork_id = i + 1;
		i++;
	}
	assign_philos(table);
	return (0);
}
