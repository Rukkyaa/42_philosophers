/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 17:45:14 by axlamber          #+#    #+#             */
/*   Updated: 2023/01/18 17:04:53 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "../libft/includes/libft.h"
# include <pthread.h>
# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data
{
	unsigned int	nb_philo;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	int				nb_of_meal;
	struct s_philo	*philos;
}				t_data;

typedef struct s_philo
{
	unsigned int	id;
	unsigned int	total_meal;
	long long		last_eat;
	pthread_t		thread;
	struct s_data	*data;
}				t_philo;

bool	parsing(int argc, char **argv, t_data *data);
void	get_info(t_data *data);
void	ft_usleep(int ms);
long long	current_time(void);
void	*routine(void *philo);

#endif