/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulayus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 13:17:31 by ulayus            #+#    #+#             */
/*   Updated: 2023/01/20 16:45:04 by ulayus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*routine()
{
	return (NULL);
}

int	main(int ac, char **av)
{
	pthread_t	*philos;
	t_philo		*philo_info;
	int			i;

	if (ac != 5 && ac != 6)
	{
		perror("Number of args invalid");
		return (1);
	}
	philo_info = init_philo(av);
	if (philo_info == NULL)
	{
		perror("Error");
		return (2);
	}
	philos = malloc(sizeof(pthread_t) * philo_info->nb_philo);
	if (philos == NULL)
		return (3);
	i = 0;
	while (i < philo_info->nb_philo)
	{
		if (pthread_create(&philos[i], NULL, &routine, NULL) != 0)
			return (4);
		i++;
	}
	i = 0;
	while (i < philo_info->nb_philo)
	{
		if (pthread_join(philos[i], NULL) != 0)
			return (5);
		i++;
	}
	display_philo_state(1, 100, FORK);
	display_philo_state(4, 300, EAT);
	display_philo_state(3, 400, SLEEP);
	display_philo_state(2, 800, THINK);
	free(philo_info);
	free(philos);
	return (0);
}
