/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 14:57:14 by nveneros          #+#    #+#             */
/*   Updated: 2025/03/28 16:34:21 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	free_philos(philos);
	free_table(table);
	return (EXIT_SUCCESS);
}
