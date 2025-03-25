/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 14:57:44 by nveneros          #+#    #+#             */
/*   Updated: 2025/03/25 10:37:49 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define MAX_UI 4294967295
# define EAT_MESSAGE "%lu %d is eating\n"
# define SLEEP_MESSAGE "%lu %d is sleeping\n"
# define THINK_MESSAGE "%lu %d is thinking\n"
# define FORK_MESSAGE "%lu %d has taken a fork\n"
# define DEAD_MESSAGE "%lu %d died\n"

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

typedef enum e_thread_status
{
	THREAD_SUCCESS,
	THREAD_DEAD,
	THREAD_END
}	t_thread_status;

typedef enum e_action
{
	SLEEP,
	EAT,
	THINK,
	FORK,
	DEAD,
}	t_action;

typedef struct s_table
{
	pthread_mutex_t	**forks;
	unsigned int	number_of_philo;
	int				required_eats_per_philo;
	unsigned long	time_at_start;
	t_bool			end_simulation;
	int				count_eat;
	pthread_mutex_t	write_access;
	pthread_mutex_t	mutex_end;
	pthread_mutex_t	mutex_count_eat;
}	t_table;

typedef struct s_philo
{
	pthread_t		thread;
	unsigned int	start_delay;
	unsigned long	time_last_eat;
	unsigned int	id;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
	t_table			*table;
}	t_philo;

// INIT
t_table			*init_table(int argc, char **argv);
t_philo			**init_philos(t_table *table, char **argv);
void			free_philos(t_philo **philos);
void			free_table(t_table *table);

// THREADS
void			add_start_delay_philos(t_philo **philos);
void			create_threads(t_philo **philos);
void			join_threads(t_philo **philos, t_table *table);
void			*routine(void	*philo_void);
t_bool			simulation_has_ended(t_table *table);
t_bool			check_philos_have_eaten(t_table *table);
void			print_message(t_action state, t_philo *philo);
t_thread_status	action(unsigned long action_time, t_action action,
					t_philo *philo);
t_thread_status	eat(t_philo *philo);
t_thread_status	take_fork_left(t_philo *philo);
t_thread_status	take_fork_right(t_philo *philo);
t_thread_status	sleep_and_check_dead(long time_action,
					t_philo *philo);

// DEBUG
void			cyan(void);
void			black(void);
void			reset(void);
void			print_table(t_table *table);
void			print_philos(t_philo **philos);
void			print_philo(t_philo *philo);

// UTILS
unsigned long	ft_atoi_ul(char *str);
void			ft_putstr_fd(char *str, int fd);
int				ft_strlen(char *str);
int				len_tab(void **tab);
t_bool			is_last_philo(t_philo **philos, int i);
unsigned long	get_time_in_milliescondes(void);

// CHECKS
t_bool			is_in_range_of_unsigned_int(char *str);
t_bool			is_valid_number(char *str);
t_bool			check_input(int argc, char **argv);

// SRC
void			assign_forks(t_table *table, t_philo **philos);
#endif