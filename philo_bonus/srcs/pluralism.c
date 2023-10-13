/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pluralism.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 22:35:25 by maalexan          #+#    #+#             */
/*   Updated: 2023/10/13 16:49:13 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	attend_dinner(t_gazer *beholder)
{
	while (!beholder->philo->terminate)
	{
		usleep(100);
		loop_simulation(beholder);
	}
	pthread_join(beholder->thread[0], NULL);
}

void	*hold_philo(void *arg)
{
	t_gazer	*beholder;

	beholder = (t_gazer *)arg;
	sem_wait(beholder->philo->done);
	beholder->philo->terminate = 1;
	pthread_join(beholder->thread[1], NULL);
	return (NULL);
}

void	threads_of_fate(t_gazer *beholder, int id)
{
	beholder->philo->id = id;
	pthread_create(&beholder->thread[0], NULL, have_dinner, beholder->philo);
	if (id % 2)
		usleep(50);
	pthread_create(&beholder->thread[1], NULL, hold_philo, beholder);
	attend_dinner(beholder);
	while (!beholder->philo->terminate)
		usleep(1000);
	leave_table(0);
}

/*
pthread_create(beholder->thread, NULL, have_dinner, beholder->philo);
pthread_join(beholder->thread, NULL);*/

/*
**	In the area of philosophy of the mind, distinguishes a position
**	where one believes there to be ultimately many kinds of substances
**	in the world, as opposed to monism and dualism.
*/
