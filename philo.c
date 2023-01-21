/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 17:00:30 by axlamber          #+#    #+#             */
/*   Updated: 2023/01/21 18:04:21 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void	eat(t_philo *voltaire)
{
	pthread_mutex_lock(&voltaire->data->forks[voltaire->l_fork]);
	print_msg(voltaire, "fork");
	pthread_mutex_lock(&voltaire->data->forks[voltaire->r_fork]);
	print_msg(voltaire, "fork");
	print_msg(voltaire, "eat");
	pthread_mutex_lock(&voltaire->data->death);
	voltaire->last_eat = current_time();
	voltaire->total_meal++;
	pthread_mutex_unlock(&voltaire->data->death);
	ft_usleep(voltaire->data->time_to_eat, voltaire->data);
	pthread_mutex_unlock(&voltaire->data->forks[voltaire->r_fork]);
	pthread_mutex_unlock(&voltaire->data->forks[voltaire->l_fork]);
}

void	*routine(void *philo)
{
	t_philo	*socrate;

	socrate = (t_philo *)philo;
	if (!(socrate->id % 2))
		ft_usleep(socrate->data->time_to_eat / 2, socrate->data);
	while (!is_dead(socrate->data))
	{
		eat(socrate);
		print_msg(socrate, "sleep");
		ft_usleep(socrate->data->time_to_sleep, socrate->data);
		print_msg(socrate, "think");
	}
	return (NULL);
}

bool	is_dead(t_data *data)
{
	bool	ret;

	pthread_mutex_lock(&data->death);
	ret = data->is_dead;
	pthread_mutex_unlock(&data->death);
	return (ret);
}

long long	get_last_eat(t_philo *philo)
{
	long long	ret;

	pthread_mutex_lock(&philo->data->death);
	ret = philo->last_eat;
	pthread_mutex_unlock(&philo->data->death);
	return (ret);
}

void	check_death(t_data *data)
{
	int	i;

	while (!data->is_dead)
	{
		i = -1;
		while ((unsigned int)++i < data->nb_philo)
		{
			if (current_time() - get_last_eat(&data->philos[i])
				>= data->time_to_die)
			{
				pthread_mutex_lock(&data->death);
				data->is_dead = 1;
				pthread_mutex_unlock(&data->death);
				pthread_mutex_lock(&data->print);
				printf("%lld %d died\n", current_time()
					- data->start_time, data->philos[i].id);
				pthread_mutex_unlock(&data->print);
				break ;
			}
			ft_usleep(100, data);
		}
	}
}
