/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fatalism.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 11:35:05 by maalexan          #+#    #+#             */
/*   Updated: 2023/10/22 14:16:03 by maalexan         ###   ########.fr       */
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
	beholder->philo.terminate = END;
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
	demise = time_of_death(&beholder->philo, beholder->die);
	if (beholder->meals && !beholder->philo.meals_left)
	{
		sem_wait(get_observer()->print);
		over_and_out(beholder);
	}
	else if (time > demise)
		death_cry(&beholder->philo);
}

/*
**	Child
*/
void	threads_of_fate(t_gazer *beholder, int id)
{
	beholder->philo.id = id;
	sem_wait(beholder->philo.done);
	sem_wait(beholder->end);
	pthread_create(&beholder->thread[0], NULL, have_dinner, &beholder->philo);
	pthread_create(&beholder->thread[1], NULL, hold_philo, beholder);
	while (!beholder->philo.terminate)
	{
		usleep(SYNC);
		loop_simulation(beholder);
	}
	pthread_join(beholder->thread[0], NULL);
	pthread_join(beholder->thread[1], NULL);
	leave_table(0);
}

/*
**	Fatalism:
**	The view that human deliberation and actions are pointless
**	and ineffectual in determining events, because whatever will
**	be will be. One ancient argument, called the idle argument,
**	went like this: "If it is fated for you to recover from your
**	illness, then you will recover whether you call a doctor or not.
**	Likewise, if you are fated not to recover, you will not do so even
**	if you call a doctor. So, calling a doctor makes no difference."
**	Arguments like this are usually rejected even by causal determinists,
**	who may say that it may be determined that only a doctor can cure you.
*/
