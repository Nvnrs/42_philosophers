/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 14:57:14 by nveneros          #+#    #+#             */
/*   Updated: 2025/03/22 15:00:21 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	philos_have_eaten(t_table *table, t_philo **philos)
{
	unsigned int	i;
	unsigned int philo_validate_meal;

	i = 0;
	philo_validate_meal = 0;
	if (table->required_eats_per_philo < 0)
		return (FALSE);
	while (philos[i])
	{
		pthread_mutex_lock(&philos[i]->mutex_count_eat);
		if (philos[i]->count_eat >= table->required_eats_per_philo)
			philo_validate_meal++;
		pthread_mutex_unlock(&philos[i]->mutex_count_eat);
		i++;
	}
	if (philo_validate_meal == table->number_of_philo)
		return (TRUE);
	return (FALSE);
}
unsigned long	get_time_in_milliescondes()
{
	struct timeval time;
	gettimeofday(&time , NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
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
	join_threads(philos, table);


	print_table(table);
	free_philos(philos);
	free_table(table);
	return (EXIT_SUCCESS);
}
