/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulayus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 16:30:41 by ulayus            #+#    #+#             */
/*   Updated: 2023/01/20 16:38:03 by ulayus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	display_philo_state(int	philo, int timestamp, int flag)
{
	if (flag == FORK)
		printf(FORK_C"%d %d has taken a fork\n"END_C, timestamp, philo);
	if (flag == EAT)
		printf(EAT_C"%d %d is eating\n"END_C, timestamp, philo);
	if (flag == SLEEP)
		printf(SLEEP_C"%d %d is sleeping\n"END_C, timestamp, philo);
	if (flag == THINK)
		printf(THINK_C"%d %d is thinking\n"END_C, timestamp, philo);
}
