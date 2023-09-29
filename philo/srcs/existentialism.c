/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   existentialism.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 16:06:47 by maalexan          #+#    #+#             */
/*   Updated: 2023/09/29 13:14:33 by maalexan         ###   ########.fr       */
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
	if (!pthread_mutex_unlock(&beholder->mutexes[second]))
	{
		ft_putstr_fd(STR_MUTEX_UNLOCK, STDERR_FILENO);
		beholder->simulating = END;
		return ;
	}
	if (!pthread_mutex_unlock(&beholder->mutexes[first]))
	{
		ft_putstr_fd(STR_MUTEX_UNLOCK, STDERR_FILENO);
		beholder->simulating = END;
		return ;
	}
	sleeping(phil, get_observer()->rest);
}

static void	pick_fork(t_phil *phil, int first, int second, t_gazer *beholder)
{
	t_bool	end;

	end = FALSE;
	if (!pthread_mutex_lock(&beholder->mutexes[first]))
	{
		if (simulating())
			printf(STR_FORK, get_time_mili(), phil->id);
		if (!pthread_mutex_lock(&beholder->mutexes[second]))
		{
			if (simulating())
				printf(STR_FORK, get_time_mili(), phil->id);
			eating(phil, beholder, first, second);
		}
		else
			end = END;
	}
	else
		end = END;
	if (end)
	{
		ft_putstr_fd(STR_MUTEX_LOCK, STDERR_FILENO);
		beholder->simulating = END;
	}
}

void	*have_dinner(void *arg)
{
	t_phil	*phil;
	int		first_fork;
	int		second_fork;

	phil = (t_phil *)arg;
	forks_priority(&first_fork, &second_fork, phil->left_fork, phil->right_fork);
	while (simulating() && phil->state)
		pick_fork(phil, first_fork - 1, second_fork - 1, get_observer());
	return (NULL);
}
