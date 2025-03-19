/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 09:58:17 by nveneros          #+#    #+#             */
/*   Updated: 2025/03/19 04:06:14 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_table(t_table *table)
{
	cyan();
	printf("___TABLE___\n");
	black();
	printf("-> **forks (count): %d\n", len_tab((void**)table->forks));
	printf("-> number_of_philo: %d\n", table->number_of_philo);
	printf("-> require_eats_per_philo: %d\n", table->required_eats_per_philo);
	printf("-> time_at_start: %lu\n", table->time_at_start);
	reset();
}
