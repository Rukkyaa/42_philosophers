/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 17:45:14 by axlamber          #+#    #+#             */
/*   Updated: 2023/02/15 12:51:23 by axlamber         ###   ########.fr       */
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
	bool			is_dead;
	long long		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	death;
	pthread_mutex_t	print;
	pthread_mutex_t	meal;
	struct s_philo	*philos;
}				t_data;

typedef struct s_philo
{
	unsigned int	id;
	unsigned int	total_meal;
	unsigned int	l_fork;
	unsigned int	r_fork;
	long long		last_eat;
	pthread_t		thread;
	struct s_data	*data;
}				t_philo;

bool		parsing(int argc, char **argv, t_data *data);
void		get_info(t_data *data);
void		ft_usleep(int ms, t_data *data);
long long	current_time(void);
void		*routine(void *philo);
void		print_msg(t_philo *philo, char *str);
void		check_death(t_data *data);
bool		is_dead(t_data *data);
bool		get_full_ate(t_data *data);
void		ft_death(t_data *data, int i);
void		eat(t_philo *voltaire);
void		take_fork(t_philo *boulesteix, bool flag);

#endif
