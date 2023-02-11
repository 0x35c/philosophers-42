/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulayus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 16:30:41 by ulayus            #+#    #+#             */
/*   Updated: 2023/02/11 17:41:42 by ulayus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_gettime(int start_time)
{
	int				time;
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	time = (current_time.tv_sec % 1000 * 1000 + current_time.tv_usec / 1000) - start_time;
	return (time);
}

void	display_philo_state(int philo, t_info *info, int flag)
{
	int	timestamp;

	timestamp = ft_gettime(info->start_time);
	if (flag == FORK)
		printf(FORK_C"%d %d has taken a fork\n"END_C, timestamp, philo);
	if (flag == EAT)
		printf(EAT_C"%d %d is eating\n"END_C, timestamp, philo);
	if (flag == SLEEP)
		printf(SLEEP_C"%d %d is sleeping\n"END_C, timestamp, philo);
	if (flag == THINK)
		printf(THINK_C"%d %d is thinking\n"END_C, timestamp, philo);
	if (flag == DIE)
		printf(DIE_C"%d %d died\n"END_C, timestamp, philo);
}
