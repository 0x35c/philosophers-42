/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulayus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 09:57:14 by ulayus            #+#    #+#             */
/*   Updated: 2023/02/11 18:44:19 by ulayus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	complete_eat_routine(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	display_philo_state(philo->philo_id, philo->info, FORK);
	pthread_mutex_lock(&(philo->right_fork));
	display_philo_state(philo->philo_id, philo->info, FORK);
	display_philo_state(philo->philo_id, philo->info, EAT);
	usleep(philo->info->time_to_eat * 1000);
	philo->last_meal = ft_gettime(philo->info->start_time);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(&(philo->right_fork));
	display_philo_state(philo->philo_id, philo->info, SLEEP);
	usleep(philo->info->time_to_sleep * 1000);
}

void	*routine(void *void_philo)
{
	t_philo	*philo;

	philo = (t_philo *)void_philo;
	philo->last_meal = 0;
	if (philo->philo_id % 2 == 0)
		usleep(100);
	while (1)
	{
		if (philo->last_meal - ft_gettime(philo->info->start_time) >= philo->info->time_to_die)
		{
			pthread_mutex_lock(&philo->death_mutex);
			*philo->death = true;
			pthread_mutex_unlock(&philo->death_mutex);
			display_philo_state(philo->philo_id, philo->info, DIE);
			break ;
		}
		pthread_mutex_lock(&philo->death_mutex);
		if (*philo->death == true)
		{
			pthread_mutex_unlock(&philo->death_mutex);
			break ;
		}
		complete_eat_routine(philo);
		display_philo_state(philo->philo_id, philo->info, THINK);
	}
	return (NULL);
}
