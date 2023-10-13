/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pluralism.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 22:35:25 by maalexan          #+#    #+#             */
/*   Updated: 2023/10/13 07:59:42 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static time_t	time_of_death(t_phil *philo, time_t die)
{
	return (philo->last_meal + die);
}

static void	loop_simulation(t_gazer *beholder)
{
	time_t	demise;
	time_t	time;

	time = get_time_micro();
	demise = time_of_death(beholder->philo, beholder->die);
	if (beholder->meals && !beholder->philo->meals_left)
		over_and_out(beholder);
	else if (time > demise)
	{
		death_cry(beholder->philo);
		over_and_out(beholder);
	}
}

void	attend_dinner(t_gazer *beholder)
{
	while (!beholder->philo->terminate)
	{
		usleep(100);
		loop_simulation(beholder);
	}
}

/*
pthread_create(beholder->thread, NULL, have_dinner, beholder->philo);
pthread_join(beholder->thread, NULL);*/

/*
**	In the area of philosophy of the mind, distinguishes a position
**	where one believes there to be ultimately many kinds of substances
**	in the world, as opposed to monism and dualism.
*/
