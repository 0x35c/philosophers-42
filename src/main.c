/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulayus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 13:17:31 by ulayus            #+#    #+#             */
/*   Updated: 2023/01/23 10:36:18 by ulayus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int ac, char **av)
{
	t_philo			*philos;
	t_philo_info	*philo_info;
	int				i;

	if (ac != 5 && ac != 6)
	{
		perror("Number of args invalid");
		return (1);
	}
	philo_info = init_philo_info(av);
	if (philo_info == NULL)
	{
		perror("Error");
		return (2);
	}
	gettimeofday(&philo_info->current_time, NULL);
	philo_info->start_time = philo_info->current_time.tv_usec;
	philos = init_philo(philo_info);
	if (philos == NULL)
		return (3);
	i = 0;
	while (i < philo_info->nb_philo)
	{
		ft_gettime(&philo_info->current_time, philo_info->start_time);
		display_philo_state(philos[i].philo_id, philo_info->current_time.tv_usec, philos[i].state);
		i++;
	}
	free(philo_info);
	free(philos);
	return (0);
}
