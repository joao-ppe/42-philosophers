/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-ppe <joao-ppe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:42:53 by joao-ppe          #+#    #+#             */
/*   Updated: 2024/01/12 18:03:59 by joao-ppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long	ft_atol(const char *str)
{
	int		i;
	int		signal;
	long	result;

	i = 0;
	result = 0;
	signal = 1;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signal = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - 48);
		i++;
	}
	return (result * signal);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}

u_int64_t	get_time(void)
{
	struct timeval	t;

	if (gettimeofday(&t, NULL))
	{
		printf("ERROR: Unable to get actual time.\n");
		return (0);
	}
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	wait_time(t_philo *philo, u_int64_t time)
{
	if ((get_time() + time) >= philo->time_to_die)
		usleep((philo->time_to_die - get_time()) * 1000);
	else
		usleep(time * 1000);
}

void	logs(t_philo *philo, int status)
{
	pthread_mutex_lock(&philo->data->log);
	if (status == EATING && !routine_finished(philo->data))
		printf("%lu %d is eating\n",
			(get_time() - philo->data->start_time), philo->id);
	else if (status == THINKING && !routine_finished(philo->data))
		printf("%lu %d is thinking\n",
			(get_time() - philo->data->start_time), philo->id);
	else if (status == SLEEPING && !routine_finished(philo->data))
		printf("%lu %d is sleeping\n",
			(get_time() - philo->data->start_time), philo->id);
	else if (status == FORK && !routine_finished(philo->data))
		printf("%lu %d has taken a fork\n",
			(get_time() - philo->data->start_time), philo->id);
	else if (status == DEAD)
		printf("%lu %d died\n",
			(get_time() - philo->data->start_time), philo->id);
	pthread_mutex_unlock(&philo->data->log);
}
