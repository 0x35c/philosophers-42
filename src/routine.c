/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulayus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 09:57:14 by ulayus            #+#    #+#             */
/*   Updated: 2023/02/06 19:46:10 by ulayus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	complete_eat_routine(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(&(philo->right_fork));
	ft_gettime(&(philo->info->current_time), philo->info->start_time);
	display_philo_state(philo->philo_id, philo->info->current_time.tv_usec, FORK);
	ft_gettime(&(philo->info->current_time), philo->info->start_time);
	display_philo_state(philo->philo_id, philo->info->current_time.tv_usec, EAT);
	usleep(philo->info->time_to_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(&(philo->right_fork));
	ft_gettime(&(philo->info->current_time), philo->info->start_time);
	display_philo_state(philo->philo_id, philo->info->current_time.tv_usec, SLEEP);
	usleep(philo->info->time_to_sleep * 1000);
}

void	*routine(void *void_philo)
{
	t_philo	*philo;

	philo = (t_philo *)void_philo;
	while (1)
	{
		if (pthread_mutex_lock(philo->left_fork) == 0
			&& pthread_mutex_lock(&(philo->right_fork)) == 0)
		{
			pthread_mutex_unlock(philo->left_fork);
			pthread_mutex_unlock(&(philo->right_fork));
			complete_eat_routine(philo);
		}
		else
		{
			ft_gettime(&(philo->info->current_time), philo->info->start_time);
			display_philo_state(philo->philo_id, philo->info->current_time.tv_usec, THINK);
		}
	}
	return (NULL);
}
