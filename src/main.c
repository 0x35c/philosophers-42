/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulayus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 13:17:31 by ulayus            #+#    #+#             */
/*   Updated: 2023/01/24 10:17:43 by ulayus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int ac, char **av)
{
	t_philo			*philos;
	t_info	*info;
	//int				i;

	if (ac != 5 && ac != 6)
	{
		perror("Number of args invalid");
		return (1);
	}
	info = init_info(av);
	if (info == NULL)
	{
		perror("Error");
		return (2);
	}
	philos = init_philo(info);
	if (philos == NULL)
		return (3);
	/*
	gettimeofday(&info->current_time, NULL);
	info->start_time = info->current_time.tv_usec;
	i = 0;
	while (i < info->nb_philo)
	{
		ft_gettime(&info->current_time, info->start_time);
		display_philo_state(philos[i].philo_id, info->current_time.tv_usec, philos[i].state);
		i++;
	}
	*/
	free(info);
	free(philos);
	return (0);
}
