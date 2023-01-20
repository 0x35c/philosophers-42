/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulayus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 13:32:01 by ulayus            #+#    #+#             */
/*   Updated: 2023/01/20 13:50:44 by ulayus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_philo	*init_philo(char **av)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (philo == NULL)
		return (NULL);
	philo->nb_philo = ft_atol(av[1]);
	philo->time_to_die = ft_atol(av[2]);
	philo->time_to_eat = ft_atol(av[3]);
	philo->time_to_sleep = ft_atol(av[4]);
	if (av[5] != NULL)
	{
		philo->nb_eat = ft_atol(av[5]);
		if (philo->nb_eat == -1)
			return (NULL);
	}
	if (philo->nb_philo == -1 || philo->time_to_die == -1
		|| philo->time_to_eat == -1 || philo->time_to_sleep == -1)
	{
		free(philo);
		return (NULL);
	}
	return (philo);
}
