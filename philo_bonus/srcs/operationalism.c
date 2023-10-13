/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operationalism.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:08:42 by maalexan          #+#    #+#             */
/*   Updated: 2023/10/13 16:38:49 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

t_bool	printer(char *str, t_phil *phil)
{
	sem_wait(get_observer()->print);
	if (phil->terminate)
	{
		sem_post(get_observer()->print);
		return (FALSE);
	}
	printf(str, get_time_mili(), phil->id);
	sem_post(get_observer()->print);
	return (TRUE);
}

void	death_cry(t_phil *phil)
{
	sem_wait(get_observer()->print);
	printf(STR_DEAD, get_time_mili(), phil->id);
	over_and_out(get_observer());
}

void	over_and_out(t_gazer *beholder)
{
	pthread_join(beholder->thread[0], NULL);
	sem_post(get_observer()->end);
	while (TRUE)
	{
		if (beholder->philo->terminate)
			break ;
	}
	while (beholder->philo->held_forks)
	{
		sem_post(beholder->forks);
		beholder->philo->held_forks--;
	}
	sem_post(get_observer()->print);
	leave_table(0);
}

static time_t	time_of_death(t_phil *philo, time_t die)
{
	return (philo->last_meal + die);
}

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
**	Operationalism:
**	The philosophy of defining a concept as the operations that will
**	measure the concept (variables) through specific observations.
*/
