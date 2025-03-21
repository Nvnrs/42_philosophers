/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 14:57:44 by nveneros          #+#    #+#             */
/*   Updated: 2025/03/21 11:49:37 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#define MAX_UI 	4294967295
#define	EAT_MESSAGE "%lu %d is eating\n"
#define	SLEEP_MESSAGE "%lu %d is sleeping\n"
#define	THINK_MESSAGE "%lu %d is thinking\n"
#define	FORK_MESSAGE "%lu %d has taken a fork\n"
#define	DEAD_MESSAGE "%lu %d died\n"

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
#include <sys/time.h>

typedef enum e_bool {
	FALSE,
	TRUE
} t_bool;

typedef enum e_status {
	SUCCESS,
	FAIL,
	STOP
} t_status;

typedef enum e_state {
	SLEEP,
	EAT,
	THINK,
	FORK,
	DEAD,
}	t_state;

typedef struct s_table
{
	pthread_mutex_t	**forks;
	unsigned int	number_of_philo;
	unsigned int	required_eats_per_philo;
	unsigned long	time_at_start;
	pthread_mutex_t write_access;
}	t_table;

typedef struct s_philo
{
	pthread_t		thread;
	// t_bool			end__thread;
	unsigned int	start_delay;
	unsigned long	time_last_eat;
	unsigned int	id;
	pthread_mutex_t *fork_left;
	pthread_mutex_t *fork_right;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	count_eat;
	int				state;
	t_table			*table;
}	t_philo;


// INIT
t_table	*init_table(int argc, char **argv);
t_philo **init_philos(t_table *table, char **argv);
void	free_philos(t_philo **philos);
void	free_table(t_table *table);

// THREADS
void	add_start_delay_philos(t_philo **philos);
void	create_threads(t_philo **philos);
void	join_threads(t_philo **philos);

// DEBUG
void	cyan();
void	black();
void	reset();
void	print_table(t_table *table);
void	print_philos(t_philo **philos);
void	print_philo(t_philo *philo);

// UTILS
unsigned long	ft_atoi_ul(char *str);
void			ft_putstr_fd(char *str, int fd);
int				ft_strlen(char *str);
int				len_tab(void **tab);
t_bool	is_last_philo(t_philo **philos, int i);
t_bool	philo_is_dead(t_philo *philo);

t_status	custom_sleep(long time_action, t_philo *philo, t_bool check_dead);

// CHECKS
t_bool	is_in_range_of_unsigned_int(char *str);
t_bool	is_valid_number(char *str);
t_bool	check_input(int argc, char **argv);

// SRC
void	assign_forks(t_table *table, t_philo **philos);
unsigned long	get_time_in_milliescondes();


// MAIN 
t_bool	philos_have_eaten(t_table *table, t_philo **philos);
#endif