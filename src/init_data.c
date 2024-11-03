/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   init_data.c                                       :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/10/17 05:12:38 by sreerink      #+#    #+#                 */
/*   Updated: 2024/10/30 17:41:38 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	check_think_time(t_table *table)
{
	int	t_think;
	int	t_eat;
	int	t_sleep;
	int	t_die;

	t_think = 0;
	t_eat = table->time_to_eat;
	t_sleep = table->time_to_sleep;
	t_die = table->time_to_die;
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
			return (false);
		philo->table = table;
		i++;
	}
	return (true);
}

int	init_data(t_table *table)
{
	int	i;

	i = 0;
	check_think_time(table);
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
