/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-ppe <joao-ppe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 22:16:46 by joao-ppe          #+#    #+#             */
/*   Updated: 2024/01/13 18:00:19 by joao-ppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	sleeping(t_philo *philo)
{
	if (routine_finished(philo->data))
		return ;
	if (is_dead(philo))
		return ;
	pthread_mutex_lock(&philo->lock);
	philo->status = SLEEPING;
	pthread_mutex_unlock(&philo->lock);
	logs(philo, SLEEPING);
	wait_time(philo, philo->data->sleep_time);
}

void	thinking(t_philo *philo)
{
	if (routine_finished(philo->data))
		return ;
	if (is_dead(philo))
		return ;
	pthread_mutex_lock(&philo->lock);
	philo->status = THINKING;
	pthread_mutex_unlock(&philo->lock);
	logs(philo, THINKING);
	wait_time(philo, 5);
}

void	eating(t_philo *philo)
{
	if (routine_finished(philo->data))
		return ;
	if (is_dead(philo))
		return ;
	if (!grab_forks(philo))
		return ;
/*  	if (routine_finished(philo->data))
	{
		pthread_mutex_unlock(philo->fork[LEFT]);
		pthread_mutex_unlock(philo->fork[RIGHT]);
		return ;
	} */
	logs(philo, EATING);
	pthread_mutex_lock(&philo->lock);
	philo->status = EATING;
	philo->time_to_die = get_time() + philo->data->death_time;
	pthread_mutex_unlock(&philo->lock);
	wait_time(philo, philo->data->eat_time);
	pthread_mutex_unlock(philo->fork[LEFT]);
	pthread_mutex_unlock(philo->fork[RIGHT]);
	pthread_mutex_lock(&philo->lock);
	philo->meal_count++;
	pthread_mutex_unlock(&philo->lock);
	return ;
}
