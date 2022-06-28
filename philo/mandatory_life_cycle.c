/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandatory_life_cycle.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acetin <acetin@student.42kocaeli.com.tr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:13:26 by acetin            #+#    #+#             */
/*   Updated: 2022/06/27 15:13:28 by acetin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	sleep_for_sleep(t_philosophers *philosopher, long long time)
{
	long long	now;

	now = get_current_time(0);
	while (get_current_time(0) - now < time)
	{
		pthread_mutex_lock(&philosopher->common->mutex);
		if (get_current_time(philosopher->last_eat)
			== philosopher->common->set_time.time_to_die)
		{
			printf("(%lld) ms philosopher (%d) is died\n",
				get_current_time(philosopher->common->set_time.start),
				philosopher->id);
			exit(EXIT_SUCCESS);
		}
		pthread_mutex_unlock(&philosopher->common->mutex);
		usleep(100);
	}
}

void	eat(t_philosophers *philosopher)
{
	if (philosopher->state == 1)
	{
		printf("(%lld) ms philosopher (%d) is eating\n",
			get_current_time(philosopher->common->set_time.start),
			philosopher->id);
		philosopher->last_eat = get_current_time(0);
		sleep_philo(philosopher->common->set_time.time_to_eat);
		philosopher->eat_count++;
		put_fork(philosopher);
	}
}

void	sleeping(t_philosophers *philosopher)
{
	if (philosopher->state == 2)
	{
		printf("(%lld) ms philosopher (%d) is sleeping\n",
			get_current_time(philosopher->common->set_time.start),
			philosopher->id);
		sleep_for_sleep(philosopher,
			philosopher->common->set_time.time_to_sleep);
		philosopher->state = 0;
		printf("(%lld) ms philosopher (%d) is thinking\n",
			get_current_time(philosopher->common->set_time.start),
			philosopher->id);
	}
}

void	think(t_philosophers *philosopher)
{
	pthread_mutex_lock(&philosopher->common->mutex);
	if (get_current_time(philosopher->last_eat)
		== philosopher->common->set_time.time_to_die)
	{
		printf("(%lld) ms philosopher (%d) is died\n",
			get_current_time(philosopher->common->set_time.start),
			philosopher->id);
		exit(EXIT_SUCCESS);
	}
	pthread_mutex_unlock(&philosopher->common->mutex);
	usleep(100);
}
