/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   existentialism.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 16:06:47 by maalexan          #+#    #+#             */
/*   Updated: 2023/10/07 14:44:56 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	sleeping(t_phil *phil, time_t rest)
{
	if (phil->state == DEAD)
		return ;
	else
		phil->state = SLEEPING;
	printer(STR_SLEEP, phil->id);
	if (simulating())
		usleep(rest);
	if (phil->state)
		phil->state = THINKING;
	printer(STR_THINK, phil->id);
}

void	eating(t_phil *phil, t_gazer *beholder)
{
	if (phil->state == DEAD)
		return ;
	else
		phil->state = EATING;
	printer(STR_EAT, phil->id);
	phil->last_meal = get_time_micro();
	if (phil->meals_left)
		phil->meals_left--;
	if (simulating())
		usleep(beholder->eat);
	if (unlock_mutex(beholder->mutexes, phil->first_fork))
		if (unlock_mutex(beholder->mutexes, phil->second_fork))
			sleeping(phil, get_observer()->rest);
}

static void	pick_fork(t_phil *phil, t_gazer *beholder)
{
	if (!simulating())
		return ;
	if (lock_mutex(phil, beholder->mutexes, phil->first_fork))
		if (lock_mutex(phil, beholder->mutexes, phil->second_fork))
			eating(phil, beholder);
}

void	*have_dinner(void *arg)
{
	t_phil	*phil;

	phil = (t_phil *)arg;
	while (simulating() && phil->state != DEAD)
		pick_fork(phil, get_observer());
	return (NULL);
}
