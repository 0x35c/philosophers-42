/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulayus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 13:21:23 by ulayus            #+#    #+#             */
/*   Updated: 2023/02/21 18:58:06 by ulayus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <sys/types.h>
# include <errno.h>
# include "struct.h"
# define FORK 1
# define EAT 2
# define SLEEP 3
# define THINK 4
# define DIE 5
# define FORK_C "\x1b[38;2;244;164;96m"
# define EAT_C "\x1b[38;2;50;205;50m"
# define SLEEP_C "\x1b[38;2;0;206;209m"
# define THINK_C "\x1b[38;2;153;50;204m"
# define DIE_C "\x1b[38;2;240;4;4m"
# define END_C "\x1b[0m"


t_info	*info_init(char **av);
t_philo	*philo_init(t_info *info);
void	display_philo_state(int philo_id, int flag, t_philo *philo);
int		ft_gettime(int start_time);
void	*routine(void *void_philo);
long	ft_atoul(const char *nptr);
void	ft_usleep(long time_to_wait, int time_to_die, t_philo *philo);

#endif
