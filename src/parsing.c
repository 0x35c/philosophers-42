/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulayus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 13:32:01 by ulayus            #+#    #+#             */
/*   Updated: 2023/01/23 10:38:35 by ulayus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_philo_info	*init_philo_info(char **av)
{
	t_philo_info	*philo_info;

	philo_info = malloc(sizeof(t_philo_info));
	if (philo_info == NULL)
		return (NULL);
	philo_info->nb_philo = ft_atoul(av[1]);
	philo_info->time_to_die = ft_atoul(av[2]);
	philo_info->time_to_eat = ft_atoul(av[3]);
	philo_info->time_to_sleep = ft_atoul(av[4]);
	if (av[5] != NULL)
	{
		philo_info->nb_eat = ft_atoul(av[5]);
		if (philo_info->nb_eat == -1)
			return (NULL);
	}
	if (philo_info->nb_philo == -1 || philo_info->time_to_die == -1
		|| philo_info->time_to_eat == -1 || philo_info->time_to_sleep == -1)
	{
		free(philo_info);
		return (NULL);
	}
	return (philo_info);
}

void	*routine(t_philo *philos)
{
	(void)philos;
	return (NULL);
}

t_philo	*init_philo(t_philo_info *philo_info)
{
	t_philo		*philos;
	int			i;	

	philos = malloc(sizeof(t_philo) * philo_info->nb_philo);
	if (philos == NULL)
		return (NULL);
	i = 0;
	while (i < philo_info->nb_philo)
	{
		if (pthread_create(&(philos[i].pthread), NULL, &routine, philos) != 0)
			return (NULL);
		if (i % 2)
			philos[i].state = FORK;
		else
			philos[i].state = SLEEP;
		philos[i].philo_id = i + 1;
		i++;
	}
	i = 0;
	while (i < philo_info->nb_philo)
	{
		if (pthread_join(philos[i].pthread, NULL) != 0)
			return (NULL);
		i++;
	}
	return (philos);
}
