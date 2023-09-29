/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pluralism.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 22:35:25 by maalexan          #+#    #+#             */
/*   Updated: 2023/09/28 21:34:23 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	oversee_dinner(t_gazer *beholder)
{
	t_uint		i;
	t_ullong	time;

	while (simulating())
	{
		i = 0;
		time = get_time_micro();
		while (i < beholder->highest)
		{
			if (time > beholder->philos[i]->last_meal)
			{
				printf(STR_DEAD, get_time_mili(), beholder->philos[i]->id);
				beholder->philos[i]->state = DEAD;
				beholder->simulating = END;
				break ;
			}
			else if (beholder->meals && !beholder->philos[i]->meals_left)
				beholder->simulating = END;
			i++;
		}
	}
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

	max = beholder->highest + 1;//fix
	threads = beholder->threads;
	phil = beholder->philos;
	if (!pthread_create(&threads[max], NULL, oversee_dinner, beholder))
		return (FALSE);
	i = 1;
	while (i < max)
	{
		if (!pthread_create(&threads[i], NULL, have_dinner, phil[i]))
			return (finish_threading(beholder, i));
		i++;
	}
	return (TRUE);
}
