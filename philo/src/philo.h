/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 14:57:44 by nveneros          #+#    #+#             */
/*   Updated: 2025/03/19 03:29:16 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#define MAX_UI 	4294967295
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>

typedef enum e_bool {
	FALSE,
	TRUE
} t_bool;

typedef enum e_state {
	SLEEP,
	EAT,
	THINK,
}	t_state;

typedef struct s_table
{
	pthread_mutex_t	**forks;
	unsigned int	number_of_philo;
	unsigned int	required_eats_per_philo;
	unsigned int	time_since_start;
}	t_table;

typedef struct s_philo
{
	pthread_t		thread;
	unsigned int	start_delay;
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
void cyan();
void black();
void reset();
void	print_table(t_table *table);
void	print_philos(t_philo **philos);
void	print_philo(t_philo *philo);

// UTILS
unsigned long	ft_atoi_ul(char *str);
void			ft_putstr_fd(char *str, int fd);
int				ft_strlen(char *str);
int				len_tab(void **tab);
t_bool	is_last_philo(t_philo **philos, int i);

// CHECKS
t_bool	is_in_range_of_unsigned_int(char *str);
t_bool	is_valid_number(char *str);
t_bool	check_input(int argc, char **argv);

// SRC
void	assign_forks(t_table *table, t_philo **philos);

#endif