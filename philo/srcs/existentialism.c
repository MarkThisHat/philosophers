/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   existentialism.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 16:06:47 by maalexan          #+#    #+#             */
/*   Updated: 2023/10/03 16:45:54 by maalexan         ###   ########.fr       */
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

void	eating(t_phil *phil, t_gazer *beholder, int first, int second)
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
	if (unlock_mutex(beholder->mutexes, first))
		if (unlock_mutex(beholder->mutexes, second))
			sleeping(phil, get_observer()->rest);
}

static void	pick_fork(t_phil *phil, int first, int second, t_gazer *beholder)
{
	t_bool	proceed;

	proceed = lock_mutex(phil, beholder->mutexes, first);
	if (simulating() && proceed)
	{
		lock_mutex(phil, beholder->mutexes, second);
		eating(phil, beholder, first, second);
	}
	else if (simulating() && !proceed)
	{
		ft_putstr_fd(STR_MUTEX_LOCK, STDERR_FILENO);
		beholder->simulating = END;
	}
}

void	*have_dinner(void *arg)
{
	t_phil	*phil;
	int		first;
	int		second;

	phil = (t_phil *)arg;
	forks_priority(&first, &second, phil->left_fork, phil->right_fork);
	while (simulating() && phil->state)
		pick_fork(phil, first - 1, second - 1, get_observer());
	return (NULL);
}
