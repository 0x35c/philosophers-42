/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulayus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 13:32:01 by ulayus            #+#    #+#             */
/*   Updated: 2023/01/24 10:17:05 by ulayus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_info	*init_info(char **av)
{
	t_info	*info;

	info = malloc(sizeof(t_info));
	if (info == NULL)
		return (NULL);
	info->nb_philo = ft_atoul(av[1]);
	info->time_to_die = ft_atoul(av[2]);
	info->time_to_eat = ft_atoul(av[3]);
	info->time_to_sleep = ft_atoul(av[4]);
	if (av[5] != NULL)
	{
		info->nb_eat = ft_atoul(av[5]);
		if (info->nb_eat == -1)
			return (NULL);
	}
	if (info->nb_philo == -1 || info->time_to_die == -1
		|| info->time_to_eat == -1 || info->time_to_sleep == -1)
	{
		free(info);
		return (NULL);
	}
	return (info);
}

t_philo	*init_philo(t_info *info)
{
	t_philo		*philos;
	int			i;	

	philos = malloc(sizeof(t_philo) * info->nb_philo);
	if (philos == NULL)
		return (NULL);
	i = 0;
	gettimeofday(&info->current_time, NULL);
	info->start_time = info->current_time.tv_usec;
	while (i < info->nb_philo)
	{
		philos[i].info = info;
		if (i % 2 == 1)
			philos[i].state = FORK;
		else
			philos[i].state = THINK;
		philos[i].philo_id = i + 1;
		if (pthread_create(&(philos[i].pthread), NULL, &routine, &philos[i]) != 0)
			return (NULL);
		i++;
	}
	i = 0;
	while (i < info->nb_philo)
	{
		if (pthread_join(philos[i].pthread, NULL) != 0)
			return (NULL);
		i++;
	}
	return (philos);
}
