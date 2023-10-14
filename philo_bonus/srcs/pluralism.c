/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pluralism.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 22:35:25 by maalexan          #+#    #+#             */
/*   Updated: 2023/10/13 21:14:23 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

/*
**	Child
*/
void	*hold_philo(void *arg)
{
	t_gazer	*beholder;

	beholder = (t_gazer *)arg;
	sem_wait(beholder->end);
	beholder->philo->terminate = END;
	return (NULL);
}

/*
**	Child
*/
static time_t	time_of_death(t_phil *philo, time_t die)
{
	return (philo->last_meal + die);
}

/*
**	Child
*/
void	loop_simulation(t_gazer *beholder)
{
	time_t	demise;
	time_t	time;

	time = get_time_micro();
	demise = time_of_death(beholder->philo, beholder->die);
	if (beholder->meals && !beholder->philo->meals_left)
	{
		sem_wait(get_observer()->print);
		over_and_out(beholder);
	}
	else if (time > demise)
		death_cry(beholder->philo);
}

/*
**	Child
*/
void	threads_of_fate(t_gazer *beholder, int id)
{
	beholder->philo->id = id;
	if (id % 2)
		usleep(50);
	pthread_create(&beholder->thread[0], NULL, have_dinner, beholder->philo);
	pthread_create(&beholder->thread[1], NULL, hold_philo, beholder);
	while (!beholder->philo->terminate)
	{
		usleep(1000);
		loop_simulation(beholder);
	}
	pthread_join(beholder->thread[0], NULL);
	pthread_join(beholder->thread[1], NULL);
	leave_table(0);
}

/*
**	In the area of philosophy of the mind, distinguishes a position
**	where one believes there to be ultimately many kinds of substances
**	in the world, as opposed to monism and dualism.
*/
