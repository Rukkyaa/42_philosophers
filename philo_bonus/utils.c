/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axlamber <axlamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 23:32:57 by rukkyaa           #+#    #+#             */
/*   Updated: 2023/02/09 17:02:45 by axlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void	print_msg(t_philo *philo, char *str)
{
	long long	time;

	sem_wait(philo->data->print);
	time = current_time() - philo->data->start_time;
	if (!ft_strncmp(str, "fork", 4))
		printf("%lld %d has taken a fork\n", time, philo->id);
	if (!ft_strncmp(str, "eat", 3))
		printf("%lld %d is eating\n", time, philo->id);
	if (!ft_strncmp(str, "sleep", 5))
		printf("%lld %d is sleeping\n", time, philo->id);
	if (!ft_strncmp(str, "think", 5))
		printf("%lld %d is thinking\n", time, philo->id);
	if (!ft_strncmp(str, "dead", 4))
		printf("%lld %d died\n", time, philo->id);
	sem_post(philo->data->print);
}

long long	current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_usleep(int ms)
{
	long long	time;

	time = current_time();
	while (current_time() - time < ms)
		usleep(10);
}
