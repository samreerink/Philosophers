/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   philo.h                                           :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/07/18 20:55:10 by sreerink      #+#    #+#                 */
/*   Updated: 2024/11/03 21:08:09 by sreerink      ########   odam.nl         */
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

typedef enum s_action
{
	EAT,
	SLEEP,
	THINK,
	TAKE_FORK,
	DIED,
} t_action;

typedef struct s_fork
{
	int				fork_id;
	pthread_mutex_t	fork;
}	t_fork;

typedef struct s_philo
{
	pthread_t		philo_thread;
	int				philo_id;
	long			n_times_eaten;
	long			last_time_eat;
	t_fork			*first;
	t_fork			*second;
	pthread_mutex_t	philo_mutex;
	t_table			*table;
}	t_philo;

struct s_table
{
	int				philo_n;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_think;
	int				max_nbr_eat;
	long			philo_start_time;
	long			n_full;
	bool			end_philo;
	bool			threads_ready;
	pthread_t		monitor_thread;
	pthread_mutex_t	table_mutex;
	pthread_mutex_t	msg_printing;
	t_fork			*forks;
	t_philo			*philos;
};

int		error_philo(const char *msg, t_table *table);
int		parse_input(char **argv, t_table *table);
int		init_data(t_table *table);
int		clean_data(t_table *table);
void	safe_set_bool(pthread_mutex_t *mtx, bool *dest, bool new_val);
bool	safe_get_bool(pthread_mutex_t *mtx, bool *val_to_get);
void	safe_set_long(pthread_mutex_t *mtx, long *dest, long new_val);
long	safe_get_long(pthread_mutex_t *mtx, long *val_to_get);
void	wait_sync_threads(t_philo *philo);
bool	simulation_finished(t_table *table);
long	get_time(void);
void	improved_usleep(int sleep_time, t_table *table);
int		philo_simulation(t_table *table);
void	*monitor(void *data);
void	*solo_philo(void *data);
void	philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	philo_think(t_philo *philo);
void	write_philo_action(t_philo *philo, t_action action);
bool	is_digit(char c);
bool	is_whitespace(char c);
void	*ft_calloc(size_t count, size_t size);
size_t	ft_strlen(const char *s);

#endif
