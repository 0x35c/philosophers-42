/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulayus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 13:32:01 by ulayus            #+#    #+#             */
/*   Updated: 2023/02/03 18:50:12 by ulayus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_info	*info_init(char **av)
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

static t_philo	*init_philos_info(t_info *info)
{
	t_philo	*philos;
	int		i;

	philos = malloc(sizeof(t_philo) * info->nb_philo);
	if (philos == NULL)
		return (NULL);
	gettimeofday(&info->current_time, NULL);
	info->start_time = info->current_time.tv_usec;
	i = 0;
	while (i < info->nb_philo - 1)
	{
		philos[i].philo_id = i + 1;
		philos[i].info = info;
		if (pthread_mutex_init(&(philos[i].right_fork), NULL))
			return (NULL);
		if (i > 0)
			philos[i].left_fork = &(philos[i - 1].right_fork);
		i++;
	}
	philos[0].left_fork = &(philos[i - 1].right_fork);
	return (philos);
}

t_philo	*philo_init(t_info *info)
{
	t_philo	*philos;
	int		i;	

	philos = init_philos_info(info);
	if (philos == NULL)
		return (NULL);
	i = 0;
	while (i < info->nb_philo - 1)
	{
		if (pthread_create(&(philos[i].pthread), NULL, &routine, &philos[i]))
			return (NULL);
		i++;
	}
	i = 0;
	while (i < info->nb_philo - 1)
	{
		if (pthread_join(philos[i].pthread, NULL))
			return (NULL);
		i++;
	}
	return (philos);
}
