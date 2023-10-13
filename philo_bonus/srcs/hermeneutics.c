/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hermeneutics.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 21:57:30 by maalexan          #+#    #+#             */
/*   Updated: 2023/10/13 12:41:47 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

t_bool	free_gazer(t_gazer *beholder)
{
	if (beholder->philo)
	{
		if (beholder->philo->done)
			sem_close(beholder->philo->done);
		free(beholder->philo);
	}
	if (beholder->pids)
		free(beholder->pids);
	return (FALSE);
}

void	end_dinner(int	final)
{
	t_gazer	*beholder;

	beholder = get_observer();
	if (beholder->forks)
	{
		sem_close(beholder->forks);
		if (final)
			sem_unlink("forks");
	}
	if (beholder->print)
	{
		sem_close(beholder->print);
		if (final)
			sem_unlink("print");
	}
	if (beholder->print)
	{
		sem_close(beholder->end);
		if (final)
			sem_unlink("end");
	}
	free_gazer(beholder);
	if (final)
		sem_unlink("philo_done");
}

void	leave_table(int code)
{
	end_dinner(0);
	exit(code);
}

/*
**	Hermeneutics:
**	The theory and methodology of interpretation. As necessary,
**	hermeneutics may include the art of understanding and communication.
**	Modern hermeneutics includes both verbal and non-verbal communication
**	as well as semiotics, presuppositions, and pre-understandings.
**	Hermeneutics has been broadly applied in the humanities, especially
**	in law, history and theology.
*/
