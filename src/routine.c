/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulayus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 09:57:14 by ulayus            #+#    #+#             */
/*   Updated: 2023/02/12 16:36:59 by ulayus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	complete_eat_routine(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	display_philo_state(philo->philo_id, philo->info, FORK);
	pthread_mutex_lock(&(philo->right_fork));
	display_philo_state(philo->philo_id, philo->info, FORK);
	display_philo_state(philo->philo_id, philo->info, EAT);
	//usleep(philo->info->time_to_eat * 1000);
	ft_usleep(philo->info->time_to_eat * 1000, philo->info.time_to_die);
	philo->last_meal = ft_gettime(philo->info->start_time);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(&(philo->right_fork));
	display_philo_state(philo->philo_id, philo->info, SLEEP);
	//usleep(philo->info->time_to_sleep * 1000);
	ft_usleep(philo->info->time_to_sleep * 1000, philo->info.time_to_die);
}

void	*routine(void *void_philo)
{
	t_philo	*philo;

	philo = (t_philo *)void_philo;
	philo->last_meal = philo->info->start_time;
	if (philo->philo_id % 2 == 0)
		usleep(100);
	while (1)
	{
		if (philo->info->time_to_eat + philo->info->time_to_sleep < philo->info->time_to_die - 10)
		complete_eat_routine(philo);
		display_philo_state(philo->philo_id, philo->info, THINK);
	}
	return (NULL);
}
