/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nveneros <nveneros@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 09:55:43 by nveneros          #+#    #+#             */
/*   Updated: 2025/03/18 10:02:30 by nveneros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void cyan()
{
  printf("\033[0;36m");
}

void black() 
{
  printf("\033[0;30m");
}

void reset()
{
  printf("\033[0m");
}
