/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 14:57:14 by nveneros          #+#    #+#             */
/*   Updated: 2025/03/28 16:21:05 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	monitor(t_table *table, t_philo **philos)
{
	unsigned int	i;
	unsigned long	actual_time;
	unsigned long	time_last_eat;
	unsigned long	time_since_last_eat;

	i = 0;
	while (table->number_of_philo > 0)
	{
		pthread_mutex_lock(&philos[i]->mutex_last_eat);
		time_last_eat = philos[i]->time_last_eat;
		pthread_mutex_unlock(&philos[i]->mutex_last_eat);
		if (time_last_eat != 0)
		{
			if (simulation_has_ended(table) 
				|| check_philos_have_eaten(table))
				break;
			actual_time = get_time_in_milliescondes();
			time_since_last_eat = (actual_time - time_last_eat);
			if (time_since_last_eat > philos[i]->time_to_die)
			{
				printf("PHILO %d ", i);
				printf("DEAD here");
				printf("time since last eat : %ld\n", time_since_last_eat);
				printf("time to die : %u\n", philos[i]->time_to_die);
				pthread_mutex_lock(&table->mutex_end);
				table->end_simulation = TRUE;
				pthread_mutex_unlock(&table->mutex_end);
				print_message(DEAD, philos[i]);
				break;
			}
		}
		if (i == table->number_of_philo - 1)
			i = 0;
		else
			i++;
	}
}

int	main(int argc, char **argv)
{
	t_philo	**philos;
	t_table	*table;

	if (!check_input(argc, argv))
		return (EXIT_FAILURE);
	table = init_table(argc, argv);
	philos = init_philos(table, argv);
	add_start_delay_philos(philos);
	assign_forks(table, philos);
	create_threads(philos);
	monitor(table, philos);
	join_threads(philos, table);
	print_table(table);
	free_philos(philos);
	free_table(table);
	return (EXIT_SUCCESS);
}