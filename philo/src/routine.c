/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulayus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 09:57:14 by ulayus            #+#    #+#             */
/*   Updated: 2023/03/08 17:56:21 by ulayus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	routine_one_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	display_philo_state(philo->philo_id, FORK, philo);
	usleep(philo->info->time_to_die * 1000);
	pthread_mutex_unlock(philo->left_fork);
	make_philo_die(philo);
}

static void	complete_eat_routine(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	display_philo_state(philo->philo_id, FORK, philo);
	pthread_mutex_lock(&(philo->right_fork));
	display_philo_state(philo->philo_id, FORK, philo);
	display_philo_state(philo->philo_id, EAT, philo);
	ft_usleep(philo->info->time_to_eat, philo->info->time_to_die, philo);
	philo->last_meal = ft_gettime(philo->info->start_time);
	pthread_mutex_lock(&philo->info->nb_meal_mutex);
	(philo->nb_meal)++;
	pthread_mutex_unlock(&philo->info->nb_meal_mutex);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(&(philo->right_fork));
	display_philo_state(philo->philo_id, SLEEP, philo);
	ft_usleep(philo->info->time_to_sleep, philo->info->time_to_die, philo);
}

static int	check_stop_conditions(t_philo *philo)
{
	if (ft_gettime(philo->info->start_time)
		- philo->last_meal >= philo->info->time_to_die)
	{
		make_philo_die(philo);
		return (true);
	}
	pthread_mutex_lock(&philo->info->can_print_mutex);
	pthread_mutex_lock(&philo->info->death_mutex);
	if (philo->death == true || *(philo->can_print) == false)
	{
		pthread_mutex_unlock(&philo->info->can_print_mutex);
		pthread_mutex_unlock(&philo->info->death_mutex);
		return (true);
	}
	pthread_mutex_unlock(&philo->info->can_print_mutex);
	pthread_mutex_unlock(&philo->info->death_mutex);
	complete_eat_routine(philo);
	pthread_mutex_lock(&philo->info->nb_meal_mutex);
	if (philo->nb_meal == philo->info->nb_meal)
	{
		pthread_mutex_unlock(&philo->info->nb_meal_mutex);
		return (true);
	}
	pthread_mutex_unlock(&philo->info->nb_meal_mutex);
	return (false);
}

void	*routine(void *void_philo)
{
	t_philo	*philo;

	philo = (t_philo *)void_philo;
	if (philo->info->nb_philo == 1)
	{
		routine_one_philo(philo);
		return (NULL);
	}
	philo->last_meal = 0;
	if (philo->philo_id % 2 == 0)
		usleep(500);
	while (1)
	{
		if (check_stop_conditions(philo) == true)
			break ;
		display_philo_state(philo->philo_id, THINK, philo);
	}
	return (NULL);
}
