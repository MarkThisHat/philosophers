/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operationalism.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:08:42 by maalexan          #+#    #+#             */
/*   Updated: 2023/10/13 21:12:08 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

/*
**	Child
*/
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

/*
**	Child
*/
void	death_cry(t_phil *phil)
{
	sem_wait(get_observer()->print);
	printf(STR_DEAD, get_time_mili(), phil->id);
	over_and_out(get_observer());
}

/*
**	Child
*/
void	over_and_out(t_gazer *beholder)
{
	sem_post(beholder->philo->done);
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
	pthread_join(beholder->thread[0], NULL);
	pthread_join(beholder->thread[1], NULL);
	leave_table(0);
}

/*
**	Operationalism:
**	The philosophy of defining a concept as the operations that will
**	measure the concept (variables) through specific observations.
*/
