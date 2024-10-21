/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   philo.h                                           :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/07/18 20:55:10 by sreerink      #+#    #+#                 */
/*   Updated: 2024/10/21 23:28:20 by sreerink      ########   odam.nl         */
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

typedef struct s_table	t_table;
typedef unsigned long	un_long;

typedef struct s_fork
{
	int				fork_id;
	pthread_mutex_t	fork;
}	t_fork;

typedef struct s_philo
{
	pthread_t		philo_thread;
	int				philo_id;
	int				n_times_eaten;
	un_long			last_time_eaten;
	bool			max_eaten;
	t_fork			*left_fork;
	t_fork			*right_fork;
	pthread_mutex_t	*philo_mutex;
	t_table			*table;
}	t_philo;

struct s_table
{
	int				philo_n;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_nbr_eat;
	un_long			philo_start_time;
	bool			end_philo_sim;
	bool			threads_ready;
	pthread_mutex_t	table_mutex;
	pthread_mutex_t	msg_printing;
	t_fork			*forks;
	t_philo			*philos;
};

int		error_philo(const char *msg, t_table *table);
int		parse_input(char **argv, t_table *table);
int		init_data(t_table *table);
void	safe_set_bool(pthread_mutex_t *mtx, bool *dest, bool new_val);
bool	safe_get_bool(pthread_mutex_t *mtx, bool *val_to_get);
void	safe_set_long(pthread_mutex_t *mtx, un_long *dest, un_long new_val);
un_long	safe_get_long(pthread_mutex_t *mtx, un_long *val_to_get);
bool	simulation_finished(t_table *table);
un_long	get_time(void);
void	improved_usleep(int sleep_time, t_table *table);
int		philo_simulation(t_table *table);
void	*ft_calloc(size_t count, size_t size);
size_t	ft_strlen(const char *s);

#endif
