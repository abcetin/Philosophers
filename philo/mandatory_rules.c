/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandatory_rules.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acetin <acetin@student.42kocaeli.com.tr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:13:47 by acetin            #+#    #+#             */
/*   Updated: 2022/06/27 15:13:48 by acetin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	all_eat(t_philosophers *philosopher)
{
	int				i;
	t_philosophers	*philo;

	i = 0;
	philo = philosopher->common->philosophers;
	while (i < philosopher->common->number_of_philosophers)
	{
		if (philo[i].eat_count
			< philosopher->common->number_of_times_each_philosopher_must_eat)
			return ;
		i++;
	}
	pthread_mutex_lock(&philosopher->common->mutex);
	exit(EXIT_SUCCESS);
}

int	can_eat(t_philosophers *philosopher)
{
	int	right;
	int	left;
	int	id;
	int	n;

	id = philosopher->id;
	n = philosopher->common->number_of_philosophers;
	right = philosopher->common->philosophers[(id + 1) % n].is_fork;
	left = philosopher->common->philosophers[((id - 1) + n) % n].is_fork;
	if (left == 0 && right == 0)
		return (1);
	return (0);
}

void	take_fork(t_philosophers *philosopher)
{
	pthread_mutex_lock(&philosopher->common->mutex);
	if (can_eat(philosopher) && !philosopher->is_fork && !philosopher->state)
	{
		philosopher->is_fork = 2;
		printf("(%lld) ms philosopher (%d) has taken a fork\n",
			get_current_time(philosopher->common->set_time.start),
			philosopher->id);
		printf("(%lld) ms philosopher (%d) has taken a fork\n",
			get_current_time(philosopher->common->set_time.start),
			philosopher->id);
		philosopher->state = 1;
	}
	pthread_mutex_unlock(&philosopher->common->mutex);
	if (philosopher->common->number_of_philosophers < 2)
	{
		printf("(%lld) ms philosopher (%d) has taken a fork\n",
			get_current_time(philosopher->common->set_time.start),
			philosopher->id);
		sleep_for_sleep(philosopher,
			philosopher->common->set_time.time_to_die);
		return ;
	}
}

void	put_fork(t_philosophers *philosopher)
{
	pthread_mutex_lock(&philosopher->common->mutex);
	if (philosopher->state == 1 && philosopher->is_fork == 2)
	{
		philosopher->is_fork = 0;
		printf("(%lld) ms philosopher (%d) has put a fork\n",
			get_current_time(philosopher->common->set_time.start),
			philosopher->id);
		printf("(%lld) ms philosopher (%d) has put a fork\n",
			get_current_time(philosopher->common->set_time.start),
			philosopher->id);
		philosopher->state = 2;
	}
	pthread_mutex_unlock(&philosopher->common->mutex);
}
