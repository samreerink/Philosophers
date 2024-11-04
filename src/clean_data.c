/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   clean_data.c                                      :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/10/27 16:41:20 by sreerink      #+#    #+#                 */
/*   Updated: 2024/11/04 20:08:43 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	free_philos(t_table *table, int n)
{
	int		i;
	t_philo	*philo;

	i = 0;
	if (!table->philos)
		return (0);
	while (i < n)
	{
		philo = table->philos + i;
		pthread_mutex_destroy(&philo->philo_mutex);
		i++;
	}
	free(table->philos);
	table->philos = NULL;
	return (0);
}

int	free_forks(t_table *table, int n)
{
	int		i;
	t_fork	*fork;

	i = 0;
	if (!table->forks)
		return (0);
	while (i < n)
	{
		fork = table->forks + i;
		pthread_mutex_destroy(&fork->fork);
		i++;
	}
	free(table->forks);
	table->forks = NULL;
	return (0);
}

void	clean_data(t_table *table)
{
	free_philos(table, table->philo_n);
	free_forks(table, table->philo_n);
	pthread_mutex_destroy(&table->table_mutex);
	pthread_mutex_destroy(&table->msg_printing);
	free(table);
}
