/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulayus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 13:39:30 by ulayus            #+#    #+#             */
/*   Updated: 2023/02/22 13:43:28 by ulayus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static bool	check_death(t_philo	*philo, int philo_id)
{
	pthread_mutex_lock(&philo->info->death_mutex);
	if (philo->death == true)
	{
		pthread_mutex_lock(&philo->info->can_print_mutex);
		*(philo->can_print) = false;
		pthread_mutex_unlock(&philo->info->death_mutex);
		pthread_mutex_unlock(&philo->info->can_print_mutex);
		pthread_mutex_lock(&philo->info->print_mutex);
		printf(DIE_C"%d %d died\n"END_C,
			ft_gettime(philo->info->start_time), philo_id);
		pthread_mutex_unlock(&philo->info->print_mutex);
		return (true);
	}
	pthread_mutex_unlock(&philo->info->death_mutex);
	return (false);
}

void	philo_manager(t_philo *philos, t_info *info)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < info->nb_philo)
		{
			if (check_death(&philos[i], i + 1) == true)
				return ;
			pthread_mutex_lock(&philos[i].info->nb_meal_mutex);
			if (philos[i].nb_meal == philos[i].info->nb_meal)
			{
				pthread_mutex_unlock(&philos[i].info->nb_meal_mutex);
				return ;
			}
			pthread_mutex_unlock(&philos[i].info->nb_meal_mutex);
			i++;
		}
	}
}
