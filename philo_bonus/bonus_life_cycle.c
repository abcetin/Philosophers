/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_life_cycle.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acetin <acetin@student.42kocaeli.com.tr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:14:32 by acetin            #+#    #+#             */
/*   Updated: 2022/06/27 15:14:34 by acetin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*dead(void *philo)
{
	t_philosophers	*philosopher;

	philosopher = (t_philosophers *)philo;
	while (1)
	{
		if (philosopher->common->must_eat
			&& philosopher->eat_count == philosopher->common->must_eat)
			break ;
		if (get_current_time(philosopher->last_eat)
			== philosopher->common->set_time.time_to_die)
		{
			sem_wait(philosopher->common->semaphore.print);
			printf("%lld ms philosopher (%d) is dead\n",
				get_current_time(philosopher->common->set_time.start),
				philosopher->id);
			exit(EXIT_FAILURE);
		}
	}
	return (NULL);
}

void	eat(t_philosophers *philosopher)
{
	sem_wait(philosopher->common->semaphore.forks);
	printf("%lld ms philosopher (%d) has taken a fork\n",
		get_current_time(philosopher->common->set_time.start),
		philosopher->id);
	sem_wait(philosopher->common->semaphore.forks);
	printf("%lld ms philosopher (%d) has taken a fork\n",
		get_current_time(philosopher->common->set_time.start),
		philosopher->id);
	printf("%lld ms philosopher (%d) is eating\n",
		get_current_time(philosopher->common->set_time.start),
		philosopher->id);
	philosopher->last_eat = get_current_time(0);
	philosopher->eat_count++;
	sleep_philo(philosopher->common->set_time.time_to_eat);
	sem_post(philosopher->common->semaphore.forks);
	sem_post(philosopher->common->semaphore.forks);
}

void	sleeping(t_philosophers *philosopher)
{
	printf("%lld ms philosopher (%d) is sleeping\n",
		get_current_time(philosopher->common->set_time.start),
		philosopher->id);
	sleep_philo(philosopher->common->set_time.time_to_sleep);
	printf("%lld ms philosopher (%d) is thinking\n",
		get_current_time(philosopher->common->set_time.start),
		philosopher->id);
}
