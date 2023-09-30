/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   existentialism.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 16:06:47 by maalexan          #+#    #+#             */
/*   Updated: 2023/09/29 22:43:35 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	sleeping(t_phil *phil, t_ullong rest)
{
	if (phil->state == DEAD)
		return ;
	phil->state = SLEEPING;
	if (simulating())
		printf(STR_SLEEP, get_time_mili(), phil->id);
	if (simulating())
		usleep(rest);
	if (simulating())
		phil->state = THINKING;
	if (simulating())
		printf(STR_THINK, get_time_mili(), phil->id);
}

void	eating(t_phil *phil, t_gazer *beholder, int first, int second)
{
	if (phil->state == DEAD)
		return ;
	phil->state = EATING;
	if (simulating())
		printf(STR_EAT, get_time_mili(), phil->id);
	phil->last_meal = get_time_micro();
	if (phil->meals_left)
		phil->meals_left--;
	if (simulating())
		usleep(beholder->eat);
	if (unlock_mutex(beholder->mutexes, first, second))
		sleeping(phil, get_observer()->rest);
}

static void	pick_fork(t_phil *phil, int first, int second, t_gazer *beholder)
{
	t_bool	proceed;

	proceed = lock_mutex(phil, beholder->mutexes, first, second);
	if (simulating() && proceed)
		eating(phil, beholder, first, second);
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
