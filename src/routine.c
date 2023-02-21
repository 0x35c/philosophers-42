/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulayus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 09:57:14 by ulayus            #+#    #+#             */
/*   Updated: 2023/02/21 18:51:05 by ulayus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	complete_eat_routine(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	display_philo_state(philo->philo_id, FORK, philo);
	pthread_mutex_lock(&(philo->right_fork));
	display_philo_state(philo->philo_id, FORK, philo);
	display_philo_state(philo->philo_id, EAT, philo);
	ft_usleep(philo->info->time_to_eat * 1000, philo->info->time_to_die, philo);
	philo->last_meal = ft_gettime(philo->info->start_time);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(&(philo->right_fork));
	display_philo_state(philo->philo_id, SLEEP, philo);
	ft_usleep(philo->info->time_to_sleep * 1000, philo->info->time_to_die, philo);
}

void	*routine(void *void_philo)
{
	t_philo	*philo;

	philo = (t_philo *)void_philo;
	//philo->last_meal = philo->info->start_time;
	if (philo->philo_id % 2 == 0)
		usleep(100);
	while (1)
	{
		if (ft_gettime(philo->info->start_time) - philo->last_meal >= philo->info->time_to_die)
		{
			pthread_mutex_lock(&philo->death_mutex);
			philo->death = true;
			pthread_mutex_unlock(&philo->death_mutex);
			break ;
		}
		pthread_mutex_lock(&philo->death_mutex);
		if (philo->death == true)
		{
			pthread_mutex_unlock(&philo->death_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->death_mutex);
		complete_eat_routine(philo);
		display_philo_state(philo->philo_id, THINK, philo);
	}
	return (NULL);
}
