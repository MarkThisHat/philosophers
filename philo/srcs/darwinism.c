/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   darwinism.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 22:35:25 by maalexan          #+#    #+#             */
/*   Updated: 2023/09/27 22:51:50 by maalexan         ###   ########.fr       */
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
				printf("%lli %i died\n",\
					get_time_mili(), beholder->philos[i]->id);
				beholder->philos[i]->state = DEAD;
				beholder->simulating = END;
			}
			else if (beholder->meals && !beholder->philos[i]->meals_left)
				beholder->simulating = END;
			i++;
		}
	}
}
