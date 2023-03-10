/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulayus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 13:25:50 by ulayus            #+#    #+#             */
/*   Updated: 2023/02/22 10:51:04 by ulayus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H
# include <pthread.h>
# include <stdbool.h>

typedef struct s_info
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_meal;
	int				start_time;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	can_print_mutex;
	pthread_mutex_t	nb_meal_mutex;
}					t_info;

typedef struct s_philo
{
	pthread_t		pthread;
	bool			death;
	bool			*can_print;
	int				nb_meal;
	int				philo_id;
	int				last_meal;
	t_info			*info;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	right_fork;
}					t_philo;

#endif
