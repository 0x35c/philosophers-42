/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulayus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 13:32:01 by ulayus            #+#    #+#             */
/*   Updated: 2023/03/08 14:32:14 by ulayus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	info_init(char **av, t_info *info)
{
	info->nb_philo = ft_atoul(av[1]);
	info->time_to_die = ft_atoul(av[2]);
	info->time_to_eat = ft_atoul(av[3]);
	info->time_to_sleep = ft_atoul(av[4]);
	if (av[5] != NULL)
	{
		info->nb_meal = ft_atoul(av[5]);
		if (info->nb_meal == -1)
			return (NULL);
	}
	else
		info->nb_meal = -2;
	if (info->nb_philo == -1 || info->time_to_die == -1
		|| info->time_to_eat == -1 || info->time_to_sleep == -1)
		return (false);
	return (true);
}

static void	*init_mutex(t_info *info)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	if (pthread_mutex_init(&info->death_mutex, NULL))
		return (NULL);
	if (pthread_mutex_init(&info->nb_meal_mutex, NULL))
		return (NULL);
	if (pthread_mutex_init(&info->can_print_mutex, NULL))
		return (NULL);
	if (pthread_mutex_init(&info->print_mutex, NULL))
		return (NULL);
	info->start_time = current_time.tv_sec % 1000 * 1000
		+ current_time.tv_usec / 1000;
	return (info);
}

static t_philo	*init_philos_info(t_info *info, bool *can_print)
{
	t_philo			*philos;
	int				i;

	philos = malloc(sizeof(t_philo) * info->nb_philo);
	if (philos == NULL)
		return (NULL);
	if (init_mutex(info) == NULL)
		return (NULL);
	i = 0;
	while (i < info->nb_philo)
	{
		philos[i].nb_meal = 0;
		philos[i].philo_id = i + 1;
		philos[i].info = info;
		philos[i].death = false;
		philos[i].can_print = can_print;
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
	bool			can_print;
	int				i;	

	can_print = true;
	philos = init_philos_info(info, &can_print);
	if (philos == NULL)
		return (NULL);
	i = 0;
	while (i < info->nb_philo)
	{
		if (pthread_create(&(philos[i].pthread), NULL, &routine, &philos[i]))
			return (NULL);
		i++;
	}
	philo_manager(philos, info);
	i = 0;
	while (i < info->nb_philo)
	{
		if (pthread_join(philos[i].pthread, NULL))
			return (NULL);
		i++;
	}
	return (philos);
}
