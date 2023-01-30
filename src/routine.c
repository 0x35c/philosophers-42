/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulayus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 09:57:14 by ulayus            #+#    #+#             */
/*   Updated: 2023/01/30 15:05:48 by ulayus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	take_forks(t_philo *philo)
{
}

void	*routine(void *void_philo)
{
	t_philo	*philo;

	philo = (t_philo *)void_philo;
	gettimeofday(&philo->info->current_time, NULL);
	philo->info->start_time = philo->info->current_time.tv_usec;
	if (philo->philo_id % 2 == 1)
	{
		philo->state = FORK;
	}	
	else
	{
		philo->state = THINK;
	}
	return (NULL);
}
