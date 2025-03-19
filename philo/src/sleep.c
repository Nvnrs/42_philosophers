/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 20:25:08 by nveneros          #+#    #+#             */
/*   Updated: 2025/03/19 21:25:37 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_remove_val(long time)
{
	long	remove;

	if (time >= 5000)
		remove = 500;
	else if (time >= 1000)
		remove = 100;
	else if (time >= 100)
		remove = 100;
	else if (time < 100 && (time - 10 ) > 0)
		remove = 10;
	else
		remove = 1;
	return (remove);
}

t_status	custom_sleep(long time, t_philo *philo)
{
	long remove;

	while (time > 0)
	{
		if (philo_is_dead(philo))
			return (FAIL);
		remove = get_remove_val(time);
		usleep(remove);
		// printf("time %ld\n", time);
		// printf("remove time %ld\n", remove);
		time -= remove;
	}
	return (SUCCESS);
}

// int	main(void)
// {
// 	custom_sleep(231123);
// 	return (0);
// }