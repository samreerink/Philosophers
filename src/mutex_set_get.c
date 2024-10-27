/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   mutex_set_get.c                                   :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/10/18 23:46:08 by sreerink      #+#    #+#                 */
/*   Updated: 2024/10/23 01:09:19 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	safe_set_bool(pthread_mutex_t *mtx, bool *dest, bool new_val)
{
	pthread_mutex_lock(mtx);
	*dest = new_val;
	pthread_mutex_unlock(mtx);
}

bool	safe_get_bool(pthread_mutex_t *mtx, bool *val_to_get)
{
	bool	val;

	pthread_mutex_lock(mtx);
	val = *val_to_get;
	pthread_mutex_unlock(mtx);
	return (val);
}

void	safe_set_long(pthread_mutex_t *mtx, long *dest, long new_val)
{
	pthread_mutex_lock(mtx);
	*dest = new_val;
	pthread_mutex_unlock(mtx);
}

long	safe_get_long(pthread_mutex_t *mtx, long *val_to_get)
{
	long	val;

	pthread_mutex_lock(mtx);
	val = *val_to_get;
	pthread_mutex_unlock(mtx);
	return (val);
}

bool	simulation_finished(t_table *table)
{
	return (safe_get_bool(&table->table_mutex, &table->end_philo));
}
