/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulayus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 13:17:31 by ulayus            #+#    #+#             */
/*   Updated: 2023/01/30 15:02:26 by ulayus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int ac, char **av)
{
	t_philo			*philos;
	t_info	*info;

	if (ac != 5 && ac != 6)
	{
		perror("Number of args invalid");
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
