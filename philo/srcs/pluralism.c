/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pluralism.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 22:35:25 by maalexan          #+#    #+#             */
/*   Updated: 2023/10/01 22:24:00 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*oversee_dinner(void *arg)
{
	t_uint	i;
	time_t	time;
	t_gazer	*beholder;

	beholder = (t_gazer *)arg;
	while (simulating())
	{
		i = 0;
		time = get_time_micro();
		while (i < beholder->highest && !beholder->simulating)
		{
			if (beholder->meals && !beholder->philos[i]->meals_left)
				beholder->simulating = END;
			else if (time > beholder->philos[i]->last_meal)
			{
				printf(STR_DEAD, get_time_mili(), beholder->philos[i]->id);
				beholder->philos[i]->state = DEAD;
				beholder->simulating = END;
			}
			i++;
		}
	}
	return (NULL);
}

t_bool	unlock_mutex(pthread_mutex_t *mutexes, int index)
{
	if (!simulating())
		return (FALSE);
	if (!pthread_mutex_unlock(&mutexes[index]))
	{
		ft_putstr_fd(STR_MUTEX_UNLOCK, STDERR_FILENO);
		get_observer()->simulating = END;
		return (FALSE);
	}
	return (TRUE);
}

t_bool	lock_mutex(t_phil *phil, pthread_mutex_t *mutexes, int first, int last)
{
	if (!simulating())
		return (FALSE);
	if (!pthread_mutex_lock(&mutexes[first]))
	{
		if (simulating())
			printf(STR_FORK, get_time_mili(), phil->id);
		else
			return (unlock_mutex(mutexes, first));
		if (!pthread_mutex_lock(&mutexes[last]))
		{
			if (simulating())
			{
				printf(STR_FORK, get_time_mili(), phil->id);
				return (TRUE);
			}
		}
	}
	return (FALSE);
}

t_bool	finish_threading(t_gazer *beholder, int max)
{
	int	i;

	i = -1;
	while (++i < max)
		pthread_join(beholder->threads[i], NULL);
	return (FALSE);
}

t_bool	start_threading(t_gazer *beholder)
{
	t_uint		i;
	t_uint		max;
	t_phil		**phil;
	pthread_t	*threads;

	max = beholder->highest + 1;
	threads = beholder->threads;
	phil = beholder->philos;
	i = 0;
	while (i < max - 1)
	{
		if (pthread_create(&threads[i], NULL, have_dinner, phil[i]))
			return (finish_threading(beholder, i));
		i++;
	}
	if (pthread_create(&threads[i], NULL, oversee_dinner, beholder))
		return (finish_threading(beholder, i));
	return (TRUE);
}
