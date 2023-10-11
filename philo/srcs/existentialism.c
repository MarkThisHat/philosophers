/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   existentialism.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 16:06:47 by maalexan          #+#    #+#             */
/*   Updated: 2023/10/11 12:57:49 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	sleeping(t_phil *phil, time_t rest)
{
	if (phil->state != OVER)
		phil->state = SLEEPING;
	printer(STR_SLEEP, phil->id);
	if (phil->state != OVER)
		usleep(rest);
	if (phil->state != OVER)
		phil->state = THINKING;
	printer(STR_THINK, phil->id);
}

void	eating(t_phil *phil, t_gazer *beholder)
{
	if (phil->state != OVER)
		phil->state = EATING;
	printer(STR_EAT, phil->id);
	phil->last_meal = get_time_micro();
	if (phil->meals_left)
		phil->meals_left--;
	if (phil->state != OVER)
		usleep(beholder->eat);
	if (phil->held_forks == 2)
		unlock_mutex(phil, beholder->mutexes, phil->second_fork);
	if (phil->held_forks == 1)
		unlock_mutex(phil, beholder->mutexes, phil->first_fork);
	sleeping(phil, get_observer()->rest);
}

static void	pick_fork(t_phil *phil, t_gazer *beholder)
{
	if (phil->state == OVER)
		return ;
	if (!phil->held_forks)
		lock_mutex(phil, beholder->mutexes, phil->first_fork);
	if (phil->held_forks == 1)
		lock_mutex(phil, beholder->mutexes, phil->second_fork);
	eating(phil, beholder);
}

static t_phil	*loneliness(t_phil *phil)
{
	t_gazer	*beholder;

	beholder = get_observer();
	lock_mutex(phil, beholder->mutexes, phil->first_fork);
	usleep(beholder->die);
	unlock_mutex(phil, beholder->mutexes, phil->first_fork);
	return (NULL);
}

void	*have_dinner(void *arg)
{
	t_phil	*phil;

	phil = (t_phil *)arg;
	if (get_observer()->highest == 1)
		return (loneliness(phil));
	while (phil->state != OVER)
		pick_fork(phil, get_observer());
	return (NULL);
}
