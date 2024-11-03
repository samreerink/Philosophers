/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   clean_data.c                                      :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/10/27 16:41:20 by sreerink      #+#    #+#                 */
/*   Updated: 2024/10/30 17:23:30 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	free_philos(t_table *table)
{
	size_t	i;
	t_philo	*philo;

	i = 0;
	while (i < table->philo_n)
	{
		philo = table->philos + i;
		pthread_mutex_destroy(&philo->philo_mutex);
		i++;
	}
	free(table->philos);
}

static void	free_forks(t_table *table)
{	
	size_t	i;
	t_fork	*fork;

	i = 0;
	while (i < table->philo_n)
	{
		fork = table->forks + i;
		pthread_mutex_destroy(&fork->fork);
		i++;
	}
	free(table->forks);
}

int	clean_data(t_table *table)
{
	free_philos(table);
	free_forks(table);
	pthread_mutex_destroy(&table->table_mutex);
	pthread_mutex_destroy(&table->msg_printing);
	free(table);
	return (1);
}
