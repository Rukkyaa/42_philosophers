/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rukkyaa <rukkyaa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:33:13 by axlamber          #+#    #+#             */
/*   Updated: 2023/01/19 10:46:27 by rukkyaa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void	print_msg(t_philo *philo, char *str)
{
	long long	time;

	time = current_time() - philo->data->start_time;
	if (!ft_strncmp(str, "fork", 4))
		printf("%lld %d has taken a fork\n", time, philo->id);
	if (!ft_strncmp(str, "eat", 3))
		printf("%lld %d is eating\n", time, philo->id);
	if (!ft_strncmp(str, "sleep", 5))
		printf("%lld %d is sleeping\n", time, philo->id);
	if (!ft_strncmp(str, "think", 5))
		printf("%lld %d is thinking\n", time, philo->id);
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
		usleep(ms / 10);
}