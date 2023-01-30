/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulayus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 13:25:50 by ulayus            #+#    #+#             */
/*   Updated: 2023/01/30 14:15:28 by ulayus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H
# include <pthread.h>

typedef struct s_info
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_eat;
	suseconds_t		start_time;
	struct timeval	current_time;
}					t_info;

typedef struct s_philo
{
	pthread_t		pthread;
	int				state;
	int				philo_id;
	t_info			*info;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	right_fork;
}				t_philo;

#endif
