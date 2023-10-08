/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pluralism.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 22:35:25 by maalexan          #+#    #+#             */
/*   Updated: 2023/10/08 10:25:36 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static time_t	time_of_death(t_phil *philo, time_t die)
{
	return (philo->last_meal + die);
}

void	*oversee_dinner(void *arg)
{
	t_uint	i;
	time_t	demise;
	t_gazer	*beholder;

	beholder = (t_gazer *)arg;
	while (simulating())
	{
		usleep(100);
		i = 0;
		while (i < beholder->highest && !beholder->simulating)
		{
			demise = time_of_death(beholder->philos[i], beholder->die);
			if (beholder->meals && !beholder->philos[i]->meals_left)
				beholder->simulating = END;
			else if (get_time_micro() > demise)
			{
				printer(STR_DEAD, beholder->philos[i]->id);
				beholder->philos[i]->state = DEAD;
				beholder->simulating = END;
			}
			i++;
		}
	}
	return (NULL);
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
