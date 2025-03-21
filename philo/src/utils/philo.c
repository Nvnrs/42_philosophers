/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:00:33 by nveneros          #+#    #+#             */
/*   Updated: 2025/03/21 14:10:28 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	is_last_philo(t_philo **philos, int i)
{
	if ((philos[i] && philos[i + 1] == NULL))
		return (TRUE);
	return (FALSE);
}
