/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-ppe <joao-ppe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 22:41:13 by joao-ppe          #+#    #+#             */
/*   Updated: 2024/01/10 23:16:03 by joao-ppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	wait_time(t_philo *philo, u_int64_t time)
{
	if ((get_time() + time) >= philo->time_to_die)
		usleep(time * 1000);
	else
		usleep((philo->time_to_die - get_time()) * 1000);
}

bool	grab_forks(t_philo *philo)
{
	if (routine_finished(philo->data))
		return (false);
	if (is_dead(philo))
		return (false);
	pthread_mutex_lock(philo->fork[LEFT]);
	logs(philo, FORK);
	if (is_dead(philo) || routine_finished(philo->data))
	{
		pthread_mutex_unlock(philo->fork[LEFT]);
		return (false);
	}
	pthread_mutex_lock(philo->fork[RIGHT]);
	logs(philo, FORK);
	if (is_dead(philo) || routine_finished(philo->data))
	{
		pthread_mutex_unlock(philo->fork[LEFT]);
		pthread_mutex_unlock(philo->fork[RIGHT]);
		return (false);
	}
	return (true);
}

/* bool	check_meals(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock);
	pthread_mutex_lock(&philo->data->lock);
	if (philo->meal_count >= philo->data->meals)
		philo->data->philos_full++;
	if (philo->data->philo_num == philo->data->philos_full)
	{
		pthread_mutex_unlock(&philo->lock);
		pthread_mutex_unlock(&philo->data->lock);
		return (true);
	}
	pthread_mutex_unlock(&philo->lock);
	pthread_mutex_unlock(&philo->data->lock);
	return (false);
}
 */
bool	routine_finished(t_data *data)
{
	pthread_mutex_lock(&data->lock);
	if (data->finished == true)
	{
		pthread_mutex_unlock(&data->lock);
		return (true);
	}
	pthread_mutex_unlock(&data->lock);
	return (false);
}

bool	is_dead(t_philo *philo)
{
	if (get_time() > philo->time_to_die)
	{
		pthread_mutex_lock(&philo->lock);
		if (philo->status != DEAD)
			philo->status = DEAD;
		pthread_mutex_unlock(&philo->lock);
		return (true);
	}
	return (false);
}

void	logs(t_philo *philo, int status)
{
	pthread_mutex_lock(&philo->data->log);
	if (status == EATING)
		printf("%lu %d is eating\n",
			(get_time() - philo->data->start_time), philo->id);
	else if (status == THINKING)
		printf("%lu %d is thinking\n",
			(get_time() - philo->data->start_time), philo->id);
	else if (status == SLEEPING)
		printf("%lu %d is sleeping\n",
			(get_time() - philo->data->start_time), philo->id);
	else if (status == FORK)
		printf("%lu %d grabbed a fork\n",
			(get_time() - philo->data->start_time), philo->id);
	else if (status == DEAD)
		printf("%lu %d died ---------------------------\n",
			(get_time() - philo->data->start_time), philo->id);
	pthread_mutex_unlock(&philo->data->log);
}
