/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulayus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 13:17:31 by ulayus            #+#    #+#             */
/*   Updated: 2023/03/08 14:31:22 by ulayus           ###   ########.fr       */
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
	t_info	info;
	bool	check;

	if (check_args(ac, av) == false)
	{
		write(2, "Invalid arguments\n", 19);
		return (1);
	}
	check = info_init(av, &info);
	if (check == false)
	{
		write(2, "Error\n", 7);
		return (2);
	}
	philos = philo_init(&info);
	if (philos == NULL)
		return (3);
	free(philos);
	return (0);
}
