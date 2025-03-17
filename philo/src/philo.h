/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 14:57:44 by nveneros          #+#    #+#             */
/*   Updated: 2025/03/17 17:23:13 by nveneros         ###   ########.fr       */
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

// UTILS
unsigned long	ft_atoi_ul(char *str);
void			ft_putstr_fd(char *str, int fd);
int				ft_strlen(char *str);

// CHECKS
t_bool	is_in_range_of_unsigned_int(char *str);
t_bool	is_valid_number(char *str);
t_bool	check_input(int argc, char **argv);

#endif