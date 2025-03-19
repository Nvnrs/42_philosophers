/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:32:07 by nveneros          #+#    #+#             */
/*   Updated: 2025/03/19 19:59:29 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	philo_is_dead(t_philo *philo)
{
	unsigned	long time_since_last_eat;

	return FALSE;
	time_since_last_eat = (philo->time_last_eat - philo->table->time_at_start);
	print_philo(philo);
	// printf("TIME _SINCE _LAST EAT : %lu\n", time_since_last_eat);
	if (time_since_last_eat >= philo->time_to_die)
	{
		philo->state = DEAD;
		return (TRUE);
	}
	return (FALSE);
}


t_status	custom_sleep(long time, t_philo *philo)
{
	int remove;

	remove = 1;
	(void)philo;
	// printf("TIME %ld\n", time);
	usleep(time);
	// while (time >= 0)
	// {
	// 	if (philo_is_dead(philo))
	// 		return (FAIL);
	// 	usleep(remove);
	// 	time -= remove;
	// }
	return (SUCCESS);
}

void	print_message(t_state state, t_philo *philo)
{
	unsigned long current_time;

	pthread_mutex_lock(&philo->table->write_access);
	current_time = get_time_in_milliescondes() - philo->table->time_at_start;
	if (state == SLEEP)
		printf(SLEEP_MESSAGE, current_time, philo->id);
	if (state == EAT)
		printf(EAT_MESSAGE, current_time, philo->id);
	if (state == THINK)
		printf(THINK_MESSAGE, current_time, philo->id);
	if (state == FORK)
		printf(FORK_MESSAGE, current_time, philo->id);
	pthread_mutex_unlock(&philo->table->write_access);
}

t_status	eat(t_philo *philo)
{
	unsigned	long time;

	time = philo->time_to_eat * 1000;
	pthread_mutex_lock(philo->fork_left);
	pthread_mutex_lock(philo->fork_right);
	philo->state = EAT;
	philo->time_last_eat = get_time_in_milliescondes();
	print_message(EAT, philo);
	if (custom_sleep(time, philo) != SUCCESS)
	{
		pthread_mutex_unlock(philo->fork_left);
		pthread_mutex_unlock(philo->fork_right);
		return (FAIL);
	}
	philo->count_eat++;
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
	return (SUCCESS);
}


t_status	action(unsigned long action_time, t_state action, t_philo *philo)
{
	long time;

	time = action_time * 1000;
	philo->state = action;
	print_message(action, philo);
	// if (time  > 0)
	// {
	usleep(time);
	// if (custom_sleep(time, philo) != SUCCESS
	//  && philo->state == DEAD)
	// {
	// 	// return (FAIL);
	// }
	return (SUCCESS);
}

void	*routine(void	*philo_void)
{
	t_philo	*philo;
	int		*status;

	philo = philo_void;
	status = malloc(sizeof(int));
	*status = SUCCESS;
	usleep(philo->start_delay * 1000);
	philo->time_last_eat = get_time_in_milliescondes();
	while (1)
	{
		// if (action(0, THINK, philo) != SUCCESS)
		*status = action(0, THINK, philo);
		// exit(0);
		if (*status == SUCCESS && philo->fork_left != NULL)
			*status = action(0, FORK, philo);
		if (*status == SUCCESS && philo->fork_right != NULL)
			*status = action(0, FORK, philo);
		if (*status == SUCCESS &&  philo->fork_left && philo->fork_right)
		{
			*status = eat(philo);
			*status = action(philo->time_to_sleep, SLEEP, philo);
		}
		if (*status == FAIL)
			return (status);
	}
	return (status);
}


void	create_threads(t_philo **philos)
{
	int	i;

	i = 0;
	while (philos[i])
	{
		pthread_create(&philos[i]->thread, NULL,
				routine, philos[i]);
		i++;
	}
}

void	join_threads(t_philo **philos)
{
	int	i;
	int	**return_val;

	i = 0;
	return_val = NULL;
	while (philos[i])
	{
		pthread_join(philos[i]->thread, (void **)return_val);
		free(*return_val);
		i++;
	}
} 

void	add_start_delay_philos(t_philo **philos)
{
	int	i;

	i = 0;
	if (len_tab((void **)philos) == 1)
		return;
	while (philos[i])
	{
		if (is_last_philo(philos, i)				
		&& len_tab((void **)philos) % 2 != 0)
		{
			philos[i]->start_delay = (philos[i]->time_to_eat * 2);
		}
		if (i % 2 != 0)
		{
			philos[i]->start_delay = philos[i]->time_to_eat;
		}
		i++;
	}
}
