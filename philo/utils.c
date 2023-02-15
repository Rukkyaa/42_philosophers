/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:33:13 by axlamber          #+#    #+#             */
/*   Updated: 2023/02/15 12:51:47 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

/*
** Function print the diferents message to send
**
** @param philo: the philo we want to print a message 
** @param str : the type of action
**
** @return: nothing 
**
** Eviter qu'une action soit affiche apres la mort -> Check a chaques actions 
** que aucun philos ne soit mort
** Eviter que les printf se melangent -> Mutex print qui se lock avant
** de print quelquechose
*/

void	print_msg(t_philo *philo, char *str)
{
	long long	time;

	if (is_dead(philo->data))
		return ;
	pthread_mutex_lock(&philo->data->print);
	time = current_time() - philo->data->start_time;
	if (!ft_strncmp(str, "fork", 4) && !is_dead(philo->data)
		&& !get_full_ate(philo->data))
		printf("%lld %d has taken a fork\n", time, philo->id);
	if (!ft_strncmp(str, "eat", 3) && !is_dead(philo->data)
		&& !get_full_ate(philo->data))
		printf("%lld %d is eating\n", time, philo->id);
	if (!ft_strncmp(str, "sleep", 5) && !is_dead(philo->data)
		&& !get_full_ate(philo->data))
		printf("%lld %d is sleeping\n", time, philo->id);
	if (!ft_strncmp(str, "think", 5) && !is_dead(philo->data)
		&& !get_full_ate(philo->data))
		printf("%lld %d is thinking\n", time, philo->id);
	if (!ft_strncmp(str, "dead", 4) && !is_dead(philo->data)
		&& !get_full_ate(philo->data))
		printf("%lld %d died\n", time, philo->id);
	pthread_mutex_unlock(&philo->data->print);
}

long long	current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_usleep(int ms, t_data *data)
{
	long long	time;

	time = current_time();
	while (current_time() - time < ms && !is_dead(data) && !get_full_ate(data))
		usleep(1000);
}

bool	get_full_ate(t_data *data)
{
	int				i;
	unsigned int	count;

	i = -1;
	count = 0;
	if (data->nb_of_meal == -1)
		return (false);
	pthread_mutex_lock(&data->meal);
	while ((unsigned int)++i < data->nb_philo)
	{
		if ((int)data->philos[i].total_meal >= data->nb_of_meal)
			count ++;
	}
	pthread_mutex_unlock(&data->meal);
	return (count == data->nb_philo);
}

void	eat(t_philo *voltaire)
{
	take_fork(voltaire, true);
	print_msg(voltaire, "eat");
	pthread_mutex_lock(&voltaire->data->death);
	voltaire->last_eat = current_time();
	pthread_mutex_lock(&voltaire->data->meal);
	voltaire->total_meal++;
	pthread_mutex_unlock(&voltaire->data->meal);
	pthread_mutex_unlock(&voltaire->data->death);
	ft_usleep(voltaire->data->time_to_eat, voltaire->data);
	take_fork(voltaire, false);
}
