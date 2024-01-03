/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-ppe <joao-ppe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 22:41:13 by joao-ppe          #+#    #+#             */
/*   Updated: 2024/01/03 14:24:01 by joao-ppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	wait_time(t_philo *philo, u_int64_t time)
{
	if ((get_time() + time) <= philo->time_to_die)
		usleep(time * 1000);
	else
		usleep((philo->time_to_die - get_time()) * 1000);
}

bool	grab_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock);
	pthread_mutex_lock(philo->fork[LEFT]);
	pthread_mutex_unlock(&philo->lock);
	logs(philo, FORK);
	if (is_dead(philo))
	{
		pthread_mutex_unlock(philo->fork[LEFT]);
		return (false);
	}
	pthread_mutex_lock(philo->fork[RIGHT]);
	logs(philo, FORK);
	if (is_dead(philo))
	{
		pthread_mutex_unlock(philo->fork[LEFT]);
		pthread_mutex_unlock(philo->fork[RIGHT]);
		return (false);
	}
	return (true);
}

bool	check_meals(t_philo *philo)
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

bool	is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->lock);
	if (get_time() > philo->time_to_die)
	{
		if (philo->status != DEAD)
		{
			philo->status = DEAD;
			//printf("||||||||||| %llu %d DIED HERE\n",
			//	(get_time() - philo->data->start_time), philo->id);
		}
		pthread_mutex_unlock(&philo->lock);
		return (true);
	}
	pthread_mutex_unlock(&philo->lock);
	return (false);
}

void	logs(t_philo *philo, int status)
{
	pthread_mutex_lock(&philo->data->log);
	if (status == EATING)
		printf("%llu %d is eating\n",
			(get_time() - philo->data->start_time), philo->id);
	else if (status == THINKING)
		printf("%llu %d is thinking\n",
			(get_time() - philo->data->start_time), philo->id);
	else if (status == SLEEPING)
		printf("%llu %d is sleeping\n",
			(get_time() - philo->data->start_time), philo->id);
	else if (status == FORK)
		printf("%llu %d grabbed a fork\n",
			(get_time() - philo->data->start_time), philo->id);
	else if (status == DEAD)
	{
		printf("%llu %d died\n",
			(get_time() - philo->data->start_time), philo->id);
		return ;
	}
	pthread_mutex_unlock(&philo->data->log);
}
