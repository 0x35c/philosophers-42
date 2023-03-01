/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulayus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 13:17:31 by ulayus            #+#    #+#             */
/*   Updated: 2023/02/23 10:13:40 by ulayus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static bool	check_args(int ac, char **av)
{
	int	i;
	int	j;

	if (ac < 5 || ac > 6)
		return (false);
	i = 1;
	while (av[i] != NULL)
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] > '9' || av[i][j] < '0')
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

int	main(int ac, char **av)
{
	t_philo	*philos;
	t_info	*info;

	if (check_args(ac, av) == false)
	{
		perror("Invalid arguments");
		return (1);
	}
	info = info_init(av);
	if (info == NULL)
	{
		perror("Error");
		return (2);
	}
	philos = philo_init(info);
	if (philos == NULL)
		return (3);
	free(info);
	free(philos);
	return (0);
}
