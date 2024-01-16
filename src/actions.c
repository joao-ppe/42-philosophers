/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-ppe <joao-ppe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 22:16:46 by joao-ppe          #+#    #+#             */
/*   Updated: 2024/01/15 16:59:51 by joao-ppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	sleeping(t_philo *philo)
{
	if (is_dead(philo) || routine_finished(philo->data))
		return ;
	pthread_mutex_lock(&philo->lock);
	philo->status = SLEEPING;
	pthread_mutex_unlock(&philo->lock);
	logs(philo, SLEEPING);
	wait_time(philo, philo->data->sleep_time);
}

void	thinking(t_philo *philo)
{
	if (is_dead(philo) || routine_finished(philo->data))
		return ;
	pthread_mutex_lock(&philo->lock);
	philo->status = THINKING;
	pthread_mutex_unlock(&philo->lock);
	logs(philo, THINKING);
	wait_time(philo, 2);
}

void	eating(t_philo *philo)
{
	if (is_dead(philo) || routine_finished(philo->data))
		return ;
	if (!grab_forks(philo))
		return ;
	if (is_dead(philo) || routine_finished(philo->data))
		return ;
	logs(philo, EATING);
	philo->time_to_die = get_time() + philo->data->death_time;
	pthread_mutex_lock(&philo->lock);
	philo->status = EATING;
	pthread_mutex_unlock(&philo->lock);
	wait_time(philo, philo->data->eat_time);
	pthread_mutex_lock(&philo->lock);
	philo->meal_count++;
	pthread_mutex_unlock(&philo->lock);
	pthread_mutex_unlock(philo->fork[LEFT]);
	pthread_mutex_unlock(philo->fork[RIGHT]);
	return ;
}
