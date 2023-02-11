/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulayus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 13:32:01 by ulayus            #+#    #+#             */
/*   Updated: 2023/02/11 18:41:30 by ulayus           ###   ########.fr       */
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

static t_philo	*init_philos_info(t_info *info, pthread_mutex_t death_mutex, bool *death)
{
	t_philo			*philos;
	struct timeval	current_time;
	int				i;

	philos = malloc(sizeof(t_philo) * info->nb_philo);
	if (philos == NULL)
		return (NULL);
	gettimeofday(&current_time, NULL);
	info->start_time = current_time.tv_sec % 1000 * 1000 + current_time.tv_usec / 1000;
	i = 0;
	while (i < info->nb_philo)
	{
		philos[i].philo_id = i + 1;
		philos[i].info = info;
		philos[i].death_mutex = death_mutex;
		philos[i].death = death;
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
	t_philo			*philos;
	pthread_mutex_t	death_mutex;
	bool			death;
	int				i;	

	death = false;
	if (pthread_mutex_init(&death_mutex, NULL))
		return (NULL);
	philos = init_philos_info(info, death_mutex, &death);
	if (philos == NULL)
		return (NULL);
	i = 0;
	while (i < info->nb_philo)
	{
		if (pthread_create(&(philos[i].pthread), NULL, &routine, &philos[i]))
			return (NULL);
		i++;
	}
	i = 0;
	while (i < info->nb_philo)
	{
		if (pthread_join(philos[i].pthread, NULL))
			return (NULL);
		i++;
	}
	return (philos);
}
