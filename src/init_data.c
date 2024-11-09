/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   init_data.c                                       :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/10/17 05:12:38 by sreerink      #+#    #+#                 */
/*   Updated: 2024/11/09 18:05:04 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	check_think_time(t_table *table)
{
	int	t_think;
	int	t_eat;
	int	t_sleep;

	t_think = 0;
	t_eat = table->time_to_eat;
	t_sleep = table->time_to_sleep;
	if (table->philo_n % 2 != 0)
	{
		t_think = t_eat * 2 - t_sleep;
		if (t_think < 0)
			t_think = 0;
	}
	table->time_to_think = t_think;
}

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
			return (free_philos(table, i));
		philo->table = table;
		i++;
	}
	return (true);
}

static bool	init_forks_mutex(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_n)
	{
		if (pthread_mutex_init(&table->forks[i].fork, NULL) != 0)
			return (free_forks(table, i));
		table->forks[i].fork_id = i + 1;
		i++;
	}
	return (true);
}

int	init_data(t_table *table)
{
	check_think_time(table);
	if (pthread_mutex_init(&table->table_mutex, NULL) != 0)
		return (error_philo("pthread_mutex_init failed\n", table));
	if (pthread_mutex_init(&table->msg_printing, NULL) != 0)
		return (error_philo("pthread_mutex_init failed\n", table));
	table->philos = ft_calloc(table->philo_n, sizeof(t_philo));
	if (!table->philos)
		return (error_philo("allocation failed\n", table));
	table->forks = ft_calloc(table->philo_n, sizeof(t_fork));
	if (!table->forks)
	{
		free_philos(table, 0);
		return (error_philo("allocation failed\n", table));
	}
	if (!init_forks_mutex(table))
	{
		free_philos(table, 0);
		return (error_philo("pthread_mutex_init failed\n", table));
	}
	if (!assign_philos(table))
		return (error_philo("pthread_mutex_init failed\n", table));
	return (0);
}
