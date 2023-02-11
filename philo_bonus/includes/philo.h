/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukkyaa <rukkyaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 17:45:14 by axlamber          #+#    #+#             */
/*   Updated: 2023/02/11 16:08:59 by rukkyaa          ###   ########.fr       */
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
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <signal.h>
# include <sys/wait.h>

typedef struct	s_data
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_of_meal;
	bool			is_dead;
	long long		start_time;
	sem_t			*forks;
	sem_t			*print;
	sem_t			*meal;
	sem_t			*death;
	sem_t			*check;
	struct s_philo	*philos;
}				t_data;

typedef struct s_philo
{
	int				id;
	int				total_meal;
	long long		last_eat;
	pthread_t		meal_thread;
	pthread_t		death_thread;
	struct s_data	*data;
}				t_philo;

bool		parsing(int argc, char **argv, t_data *data);
long long	current_time(void);
void		ft_usleep(int ms, t_data *data);
bool		init_philos(t_data *data);
void		routine_philo(t_philo *notch);
void		print_msg(t_philo *philo, char *str);
bool		is_dead(t_data *data);

#endif
