/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   existentialism.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 16:06:47 by maalexan          #+#    #+#             */
/*   Updated: 2023/09/27 22:33:39 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	sleeping(t_phil *phil, t_ullong rest)
{
	if (phil->state == DEAD)
		return ;
	phil->state = SLEEPING;
	if (simulating())
		printf("%lli %i is sleeping\n", get_time_mili(), phil->id);
	if (simulating())
		usleep(rest);
	if (simulating())
		phil->state = THINKING;
	if (simulating())
		printf("%lli %i is thinking\n", get_time_mili(), phil->id);
}

void	eating(t_phil *phil, t_ullong eat)
{
	if (phil->state == DEAD)
		return ;
	phil->state = EATING;
	if (simulating())
		printf("%lli %i is eating\n", get_time_mili(), phil->id);
	phil->last_meal = get_time_micro();
	if (phil->meals_left)
		phil->meals_left--;
	if (simulating())
		usleep(eat);
	sleeping(phil, get_observer()->rest);
}

static void	pick_fork(t_phil *phil, int first, int second, t_gazer *beholder)
{
	t_bool	end;

	if (phil->state == DEAD)
		return ;
	end = FALSE;
	if (pthread_mutex_lock(&beholder->mutexes[first]))
	{
		if (pthread_mutex_lock(&beholder->mutexes[second]))
		{
			eating(phil, beholder->eat);
			if (pthread_mutex_unlock(&beholder->mutexes[second]))
				end = END;
		}
		else
			end = END;
		if (pthread_mutex_unlock(&beholder->mutexes[first]))
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

void	have_dinner(t_phil *phil, t_gazer *beholder)
{
	int	first_fork;
	int	second_fork;

	set_cutlery(&first_fork, &second_fork, phil->left_fork, phil->right_fork);
	while (simulating() && phil->state)
		pick_fork(phil, first_fork, second_fork, beholder);
}
