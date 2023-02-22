/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulayus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 16:30:41 by ulayus            #+#    #+#             */
/*   Updated: 2023/02/22 09:59:00 by ulayus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_gettime(int start_time)
{
	int				time;
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	time = (current_time.tv_sec % 1000 * 1000 + current_time.tv_usec / 1000) - start_time;
	return (time);
}

void	make_philo_die(t_philo *philo)
{
	pthread_mutex_lock(&philo->death_mutex);
	philo->death = true;
	pthread_mutex_unlock(&philo->death_mutex);
}

void	ft_usleep(int time_to_wait, int time_to_die, t_philo *philo)
{
	long	timestamp;
	long	start;

	start = ft_gettime(philo->info->start_time);
	timestamp = ft_gettime(philo->info->start_time) - start;
	//printf("Total time to die: %d\n", time_to_die);
	//printf("Total time to wait: %d\n", time_to_wait);
	//printf("Start value: %ld\n", start);
	while (timestamp <= time_to_wait)
	{
		//printf("Timestamp value: %ld\n", timestamp);
		if (timestamp >= time_to_die)
		{
			make_philo_die(philo);
			//printf("NTM ANTO\n");
			break ;
		}	
		if (ft_gettime(philo->info->start_time) - philo->last_meal >= philo->info->time_to_die)
		{
			pthread_mutex_lock(&philo->death_mutex);
			philo->death = true;
			pthread_mutex_unlock(&philo->death_mutex);
			break ;
		}
		usleep(400);
		timestamp = ft_gettime(philo->info->start_time) - start;
		//printf("Waiting once...\n");
	}
	//printf("Waitig once...\n");
}

void	display_philo_state(int philo_id, int flag, t_philo *philo)
{
	int	timestamp;

	pthread_mutex_lock(&philo->print_mutex);
	if (*(philo->print) == false)
	{
		pthread_mutex_unlock(&philo->print_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->print_mutex);
	timestamp = ft_gettime(philo->info->start_time);
	if (flag == FORK)
		printf(FORK_C"%d %d has taken a fork\n"END_C, timestamp, philo_id);
	if (flag == EAT)
		printf(EAT_C"%d %d is eating\n"END_C, timestamp, philo_id);
	if (flag == SLEEP)
		printf(SLEEP_C"%d %d is sleeping\n"END_C, timestamp, philo_id);
	if (flag == THINK)
		printf(THINK_C"%d %d is thinking\n"END_C, timestamp, philo_id);
}
