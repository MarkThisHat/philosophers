/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   existentialism.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 16:06:47 by maalexan          #+#    #+#             */
/*   Updated: 2023/10/13 21:12:45 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

/*
**	Child
*/
void	sleeping(t_phil *phil, time_t rest)
{
	printer(STR_SLEEP, phil);
	if (!phil->terminate)
		usleep(rest);
	printer(STR_THINK, phil);
}

/*
**	Child
*/
void	eating(t_phil *phil, t_gazer *beholder)
{
	printer(STR_EAT, phil);
	phil->last_meal = get_time_micro();
	if (phil->meals_left)
		phil->meals_left--;
	if (!phil->terminate)
		usleep(beholder->eat);
	while (phil->held_forks)
	{
		sem_post(beholder->forks);
		phil->held_forks--;
	}
	sleeping(phil, get_observer()->rest);
}

/*
**	Child
*/
static void	pick_fork(t_phil *phil, t_gazer *beholder)
{
	if (phil->terminate)
		return ;
	if (!phil->held_forks)
	{
		sem_wait(beholder->forks);
		phil->held_forks++;
	}
	if (phil->held_forks == 1)
	{
		sem_wait(beholder->forks);
		phil->held_forks++;
	}
	eating(phil, beholder);
}

/*
**	Child
*/
static t_phil	*loneliness(t_gazer *beholder)
{
	sem_wait(beholder->forks);
	usleep(beholder->die);
	sem_post(beholder->forks);
	return (NULL);
}

/*
**	Child
*/
void	*have_dinner(void *arg)
{
	t_phil	*phil;

	phil = (t_phil *)arg;
	if (get_observer()->highest == 1)
		return (loneliness(get_observer()));
	while (!phil->terminate)
		pick_fork(phil, get_observer());
	return (NULL);
}

/*
**	Existentialism:
**	The philosophical movement that views human existence
**	as having a set of underlying themes and characteristics,
**	such as anxiety, dread, freedom, awareness of death, and
**	consciousness of existing, that are primary. That is, they
**	cannot be reduced to or explained by a natural-scientific
**	approach or any approach that attempts to detach itself 
**	from or rise above these themes.
*/
