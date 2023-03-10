/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulayus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 16:30:41 by ulayus            #+#    #+#             */
/*   Updated: 2023/03/11 12:36:42 by ulayus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_gettime(int start_time)
{
	int				time;
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	time = (current_time.tv_sec % 1000 * 1000 + current_time.tv_usec / 1000)
		- start_time;
	return (time);
}

void	make_philo_die(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->death_mutex);
	philo->death = true;
	pthread_mutex_unlock(&philo->info->death_mutex);
}

void	ft_usleep(int time_to_wait, int time_to_die, t_philo *philo)
{
	long	timestamp;
	long	start;

	start = ft_gettime(philo->info->start_time);
	timestamp = ft_gettime(philo->info->start_time) - start;
	while (timestamp <= time_to_wait)
	{
		if (timestamp >= time_to_die || ft_gettime(philo->info->start_time)
			- philo->last_meal >= philo->info->time_to_die)
		{
			make_philo_die(philo);
			break ;
		}	
		usleep(500);
		timestamp = ft_gettime(philo->info->start_time) - start;
	}
}

void	display_philo_state(int philo_id, int flag, t_philo *philo)
{
	int	timestamp;

	pthread_mutex_lock(&philo->info->can_print_mutex);
	if (*(philo->can_print) == false)
	{
		pthread_mutex_unlock(&philo->info->can_print_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->info->can_print_mutex);
	timestamp = ft_gettime(philo->info->start_time);
	pthread_mutex_lock(&philo->info->print_mutex);
	if (flag == FORK)
		printf(FORK_C"%d %d has taken a fork\n"END_C, timestamp, philo_id);
	if (flag == EAT)
		printf(EAT_C"%d %d is eating\n"END_C, timestamp, philo_id);
	if (flag == SLEEP)
		printf(SLEEP_C"%d %d is sleeping\n"END_C, timestamp, philo_id);
	if (flag == THINK)
		printf(THINK_C"%d %d is thinking\n"END_C, timestamp, philo_id);
	pthread_mutex_unlock(&philo->info->print_mutex);
}
