/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   monitor.c                                         :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/10/22 20:54:21 by sreerink      #+#    #+#                 */
/*   Updated: 2024/11/03 21:48:15 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static bool	all_philos_full(t_table *t)
{
	return (safe_get_long(&t->table_mutex, &t->n_full) == t->philo_n);
}

static bool	philo_died(t_philo *p)
{
	long	t_to_die;
	long	last_time_eat;
	long	t_since_meal;

	t_to_die = p->table->time_to_die;
	last_time_eat = safe_get_long(&p->philo_mutex, &p->last_time_eat);
	if (last_time_eat == 0)
		last_time_eat = p->table->philo_start_time;
	t_since_meal = get_time() - last_time_eat;
	if (t_since_meal >= t_to_die)
	{
		safe_set_bool(&p->table->table_mutex, &p->table->end_philo, true);
		write_philo_action(p, DIED);
		return (true);
	}
	return (false);
}

void	*monitor(void *data)
{
	int		i;
	t_table	*table;

	table = (t_table *)data;
	while (!safe_get_bool(&table->table_mutex, &table->threads_ready))
		;
	while (1)
	{
		i = 0;
		while (i < table->philo_n)
		{
			if (philo_died(table->philos + i))
				return (NULL);
			if (all_philos_full(table))
			{
				safe_set_bool(&table->table_mutex, &table->end_philo, true);
				return (NULL);
			}
			i++;
		}
	}
	return (NULL);
}
