/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulayus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 16:30:41 by ulayus            #+#    #+#             */
/*   Updated: 2023/02/03 18:56:41 by ulayus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_gettime(struct timeval *current_time, suseconds_t start_time)
{
	gettimeofday(current_time, NULL);
	current_time->tv_usec /= 1000;
	current_time->tv_usec -= (start_time / 1000);
}

void	display_philo_state(int philo, suseconds_t timestamp, int flag)
{
	if (flag == FORK)
		printf(FORK_C"%ld %d has taken a fork\n"END_C, timestamp, philo);
	if (flag == EAT)
		printf(EAT_C"%ld %d is eating\n"END_C, timestamp, philo);
	if (flag == SLEEP)
		printf(SLEEP_C"%ld %d is sleeping\n"END_C, timestamp, philo);
	if (flag == THINK)
		printf(THINK_C"%ld %d is thinking\n"END_C, timestamp, philo);
}
