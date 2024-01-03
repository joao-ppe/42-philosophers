/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-ppe <joao-ppe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:22:50 by joao-ppe          #+#    #+#             */
/*   Updated: 2024/01/03 14:03:49 by joao-ppe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/*------------- Includes ---------------*/
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <fcntl.h>
# include <limits.h>
# include <stdint.h>
# include <stdbool.h>
# include <sys/time.h>
# include <pthread.h>

/*------------- Variables ---------------*/
enum e_forks
{
	LEFT,
	RIGHT
};

enum e_actions
{
	DEAD,
	EATING,
	SLEEPING,
	THINKING,
	FORK,
	FULL
};

/*------------- Structures ---------------*/
typedef struct s_philo
{
	struct s_data	*data;
	int				id;
	int				meal_count;
	int				status;
	bool			full;
	bool			finished;
	u_int64_t		time_to_die;
	pthread_mutex_t	lock;
	pthread_mutex_t	*fork[2];
}					t_philo;

typedef struct s_data
{
	pthread_t		*monitor;
	pthread_t		*table;
	t_philo			*philos;
	int				philo_num;
	int				meals;
	bool			finished;
	int				philos_full;
	u_int64_t		death_time;
	u_int64_t		eat_time;
	u_int64_t		sleep_time;
	u_int64_t		start_time;
	pthread_mutex_t	lock;
	pthread_mutex_t	*forks;
	pthread_mutex_t	log;
}					t_data;

/*------------- Functions ---------------*/
/// MAIN ///
int			main(int ac, char **av);
/// CHECKS ///
int			check_input(char **av);
/// INITS ///
t_data		*init_data(int ac, char **av);
/// UTILS ///
long		ft_atol(const char *str);
int			ft_isdigit(int c);
u_int64_t	get_time(void);
// ROUTINE ///
void		reunion(t_data *data);
void		*routine(void *philo);
void		*monitoring(void *struc);
/// ACTIONS ///
void		sleeping(t_philo *philo);
void		thinking(t_philo *philo);
void		eating(t_philo *philo);
/// ROUTINE_UTILS ///
void		wait_time(t_philo *philo, u_int64_t time);
bool		grab_forks(t_philo *philo);
bool		is_dead(t_philo *philo);
void		logs(t_philo *philo, int status);
/// FREE ///
void    	free_data(t_data *data);

#endif
