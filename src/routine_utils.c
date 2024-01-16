/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-ppe <joao-ppe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 22:41:13 by joao-ppe          #+#    #+#             */
/*   Updated: 2024/01/16 16:44:22 by joao-ppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	grab_forks(t_philo *philo)
{
	if (is_dead(philo) || routine_finished(philo->data))
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

bool	check_meals(t_philo *philo)
{
	if (philo->data->meals == -1)
		return (false);
	if ((philo->meal_count >= philo->data->meals)
		&& philo->full == false)
	{
		philo->full = true;
		philo->data->philos_full++;
	}
	if (philo->data->philo_num == philo->data->philos_full)
		return (true);
	return (false);
}

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

bool	check_philo_status(t_philo *philo)
{
	if (philo->status == DEAD || check_meals(philo))
	{
		pthread_mutex_lock(&philo->data->lock);
		philo->data->finished = true;
		pthread_mutex_unlock(&philo->data->lock);
		if (philo->status == DEAD)
			logs(philo, DEAD);
		return (true);
	}
	return (false);
}

bool	is_dead(t_philo *philo)
{
	if (get_time() >= philo->time_to_die)
	{
		pthread_mutex_lock(&philo->lock);
		if (philo->status != DEAD)
			philo->status = DEAD;
		pthread_mutex_unlock(&philo->lock);
		return (true);
	}
	return (false);
}
