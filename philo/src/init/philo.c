/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 11:05:59 by nveneros          #+#    #+#             */
/*   Updated: 2025/03/27 15:12:12 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*init_philo(t_table *table, char **argv, int index)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (philo == NULL)
		return (NULL);
	philo->id = index + 1;
	philo->start_delay = 0;
	philo->time_last_eat = 0;
	philo->time_to_die = ft_atoi_ul(argv[2]);
	philo->time_to_eat = ft_atoi_ul(argv[3]);
	philo->time_to_sleep = ft_atoi_ul(argv[4]);
	philo->table = table;
	pthread_mutex_init(&philo->mutex_last_eat, NULL);
	return (philo);
}

t_philo	**init_philos(t_table *table, char **argv)
{
	unsigned int	i;
	t_philo			**philos;

	i = 0;
	philos = malloc((table->number_of_philo + 1) * sizeof(t_philo *));
	while (i < table->number_of_philo)
	{
		philos[i] = init_philo(table, argv, i);
		i++;
	}
	philos[i] = NULL;
	return (philos);
}

void	free_philos(t_philo **philos)
{
	unsigned int	i;

	i = 0;
	while (philos[i])
	{
		pthread_mutex_destroy(&philos[i]->mutex_last_eat);
		free(philos[i]);
		i++;
	}
	free(philos);
}
