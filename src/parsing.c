/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulayus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 13:32:01 by ulayus            #+#    #+#             */
/*   Updated: 2023/02/22 10:29:42 by ulayus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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
		info->nb_meal = ft_atoul(av[5]);
		if (info->nb_meal == -1)
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

static t_philo	*init_philos_info(t_info *info, pthread_mutex_t death_mutex,
				pthread_mutex_t print_mutex, pthread_mutex_t nb_meal_mutex, bool *print)
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
		philos[i].nb_meal = 0;
		philos[i].philo_id = i + 1;
		philos[i].info = info;
		philos[i].death_mutex = death_mutex;
		philos[i].death = false;
		philos[i].print_mutex = print_mutex;
		philos[i].print = print;
		philos[i].nb_meal_mutex = nb_meal_mutex;
		if (pthread_mutex_init(&(philos[i].right_fork), NULL))
			return (NULL);
		if (i > 0)
			philos[i].left_fork = &(philos[i - 1].right_fork);
		i++;
	}
	philos[0].left_fork = &(philos[i - 1].right_fork);
	return (philos);
}

void	philo_manager(t_philo *philos, t_info *info)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < info->nb_philo)
		{
			pthread_mutex_lock(&philos[i].death_mutex);
			if (philos[i].death == true)
			{
				pthread_mutex_lock(&philos[i].print_mutex);
				*(philos[i].print) = false;
				pthread_mutex_unlock(&philos[i].death_mutex);
				pthread_mutex_unlock(&philos[i].print_mutex);
				printf(DIE_C"%d %d died\n"END_C,
					ft_gettime(philos[i].info->start_time), i + 1);
				return ;
			}
			pthread_mutex_unlock(&philos[i].death_mutex);
			pthread_mutex_lock(&philos[i].nb_meal_mutex);
			if (philos[i].nb_meal == philos[i].info->nb_meal)
			{
				pthread_mutex_unlock(&philos[i].nb_meal_mutex);
				return ;
			}
			pthread_mutex_unlock(&philos[i].nb_meal_mutex);
			i++;
		}
	}
}

t_philo	*philo_init(t_info *info)
{
	t_philo			*philos;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	nb_meal_mutex;
	bool			print;
	int				i;	

	if (pthread_mutex_init(&death_mutex, NULL))
		return (NULL);
	if (pthread_mutex_init(&nb_meal_mutex, NULL))
		return (NULL);
	print = true;
	if (pthread_mutex_init(&print_mutex, NULL))
		return (NULL);
	philos = init_philos_info(info, death_mutex, print_mutex, nb_meal_mutex, &print);
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
