/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   philo_actions.c                                   :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/10/22 00:59:32 by sreerink      #+#    #+#                 */
/*   Updated: 2024/10/22 04:53:17 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	write_philo_action(t_philo *philo, t_action action)
{
	long	timestamp;

	timestamp = get_time() - philo->table->philo_start_time;
	pthread_mutex_lock(&philo->table->msg_printing);
	if (action == TAKE_FORK && !simulation_finished(philo->table))
		printf("%lu %d has taken a fork\n", timestamp, philo->philo_id);
	else if (action == EAT && !simulation_finished(philo->table))
		printf("%lu %d is eating\n", timestamp, philo->philo_id);
	else if (action == SLEEP && !simulation_finished(philo->table))
		printf("%lu %d is sleeping\n", timestamp, philo->philo_id);
	else if (action == THINK && !simulation_finished(philo->table))
		printf("%lu %d is thinking\n", timestamp, philo->philo_id);
	else if (action == DIED && !simulation_finished(philo->table))
		printf("%lu %d died\n", timestamp, philo->philo_id);
	pthread_mutex_unlock(&philo->table->msg_printing);
}

void	philo_eat(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	pthread_mutex_lock(&philo->first->fork);
	write_philo_action(philo, TAKE_FORK);
	pthread_mutex_lock(&philo->second->fork);
	write_philo_action(philo, TAKE_FORK);
	safe_set_long(&philo->philo_mutex, &philo->last_time_eaten, get_time());
	write_philo_action(philo, EAT);
	if (simulation_finished(table))
		return ;
	improved_usleep(table->time_to_eat, table);
	philo->n_times_eaten++;
	pthread_mutex_unlock(&philo->first->fork);
	pthread_mutex_unlock(&philo->second->fork);
	if (philo->n_times_eaten == table->max_nbr_eat)
		philo->max_eaten = true;
}

void	philo_sleep(t_philo *philo)
{
	write_philo_action(philo, SLEEP);
	if (simulation_finished(philo->table))
		return ;
	improved_usleep(philo->table->time_to_sleep, philo->table);
}

void	philo_think(t_philo *philo)
{
	write_philo_action(philo, THINK);
}
