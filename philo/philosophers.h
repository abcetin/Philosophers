/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acetin <acetin@student.42kocaeli.com.tr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:14:04 by acetin            #+#    #+#             */
/*   Updated: 2022/06/27 15:14:05 by acetin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>

typedef struct s_philosophers	t_philosophers;

typedef struct s_time
{
	long long		start;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
}	t_time;

typedef struct s_common
{
	t_time			set_time;
	t_philosophers	*philosophers;
	pthread_mutex_t	mutex;
	pthread_t		die;
	int				number_of_times_each_philosopher_must_eat;
	int				number_of_philosophers;
}	t_common;

typedef struct s_philosophers
{
	int				id;
	pthread_t		th;
	t_common		*common;
	long long		last_eat;
	int				is_fork;
	int				state;
	int				eat_count;
}	t_philosophers;

//-------utils------------//
int			ft_atoi(const char *str);
int			check_arg(t_common *common, char **arg);
//-------sleep------------//
void		sleep_philo(long long time);
long long	get_current_time(long long time);
void		sleep_for_sleep(t_philosophers *philosopher, long long time);
//-------life-cycle------------//
void		think(t_philosophers *philosopher);
void		sleeping(t_philosophers *philosopher);
void		eat(t_philosophers *philosopher);
//-------rules------------//
void		put_fork(t_philosophers *philosopher);
void		take_fork(t_philosophers *philosopher);
int			have_a_fork(t_philosophers *philosopher);
void		all_eat(t_philosophers *philosopher);
#endif
