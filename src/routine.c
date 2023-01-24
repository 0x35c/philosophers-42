/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulayus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 09:57:14 by ulayus            #+#    #+#             */
/*   Updated: 2023/01/24 10:38:02 by ulayus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*routine(void *void_philo)
{
	t_philo	*philo;

	philo = (t_philo *)void_philo;
	if (philo->state == FORK)
	{
		ft_gettime(&philo->info->current_time, philo->info->start_time);
		display_philo_state(philo->philo_id, philo->info->current_time.tv_usec, philo->state);
		usleep(philo->info->time_to_eat);
		philo->state = SLEEP;
	}	
	else if (philo->state == THINK)
	{
		ft_gettime(&philo->info->current_time, philo->info->start_time);
		display_philo_state(philo->philo_id, philo->info->current_time.tv_usec, philo->state);
		usleep(philo->info->time_to_die);
	}
	return (NULL);
}
