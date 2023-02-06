/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulayus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 09:57:14 by ulayus            #+#    #+#             */
/*   Updated: 2023/02/06 12:24:37 by ulayus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*routine(void *void_philo)
{
	t_philo	*philo;

	philo = (t_philo *)void_philo;
	while (1)
	{
		if (philo->philo_id % 2 == 1)
			philo->state = FORK;
		else
		{
			philo->state = THINK;
			ft_gettime(&(philo->info->current_time), philo->info->start_time);
			display_philo_state(philo->philo_id, philo->info->current_time.tv_usec, THINK);
		}
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(&(philo->right_fork));
		ft_gettime(&(philo->info->current_time), philo->info->start_time);
		display_philo_state(philo->philo_id, philo->info->current_time.tv_usec, FORK);
		display_philo_state(philo->philo_id, philo->info->current_time.tv_usec, EAT);
		usleep(philo->info->time_to_eat * 1000);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(&(philo->right_fork));
		usleep(philo->info->time_to_sleep * 1000);
	}
	return (NULL);
}
