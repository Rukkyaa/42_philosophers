/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 17:45:14 by axlamber          #+#    #+#             */
/*   Updated: 2023/02/09 16:52:15 by axlamber         ###   ########.fr       */
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
	sem_t			*death;
	struct s_philo	*philos;
}				t_data;

typedef struct s_philo
{
	int				id;
	int				total_meal;
	long long		last_eat;
	struct s_data	*data;
}				t_philo;

bool		parsing(int argc, char **argv, t_data *data);
long long	current_time(void);
void		ft_usleep(int ms);
bool		init_philos(t_data *data);
void		routine_philo(t_philo *notch);
void		print_msg(t_philo *philo, char *str);

#endif
