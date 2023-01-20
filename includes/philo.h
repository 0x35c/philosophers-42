/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulayus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 13:21:23 by ulayus            #+#    #+#             */
/*   Updated: 2023/01/20 16:47:42 by ulayus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <pthread.h>
# include "struct.h"
# define FORK 1
# define EAT 2
# define SLEEP 3
# define THINK 4
# define FORK_C "\x1b[38;2;244;164;96m"
# define EAT_C "\x1b[38;2;50;205;50m"
# define SLEEP_C "\x1b[38;2;0;206;209m"
# define THINK_C "\x1b[38;2;153;50;204m"
# define END_C "\x1b[0m"


t_philo	*init_philo(char **av);
void	display_philo_state(int philo, int timestamp, int flag);
long	ft_atol(const char *nptr);

#endif
