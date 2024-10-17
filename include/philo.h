/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   philo.h                                           :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/07/18 20:55:10 by sreerink      #+#    #+#                 */
/*   Updated: 2024/10/17 03:22:06 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/time.h>
# include <limits.h>
# include <pthread.h>

typedef pthread_mutex_t	t_mtx;

typedef struct s_fork
{
	int		fork_id;
	t_mtx	fork;
}	t_fork;

typedef struct s_philo
{
	pthread_t	philo_thread;
	int			philo_id;
	long		n_times_eaten;
	long		last_time_eaten;
	bool		max_eaten;
	t_fork		*left_fork;
	t_fork		*right_fork;
}	t_philo;

typedef struct s_table
{
	long	philo_n;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	max_nbr_eat;
	long	start_philo_time;
	bool	end_philo_sim;
	t_mtx	msg_printing;
	t_fork	*forks;
	t_philo	*philos;
}	t_table;

int		error_philo(const char *msg, t_table *table);
int		parse_input(char **argv, t_table *table);
void	*ft_calloc(size_t count, size_t size);
size_t	ft_strlen(const char *s);

#endif
