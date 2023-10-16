/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hermeneutics.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 21:57:30 by maalexan          #+#    #+#             */
/*   Updated: 2023/10/15 23:10:44 by maalexan         ###   ########.fr       */
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

void	clear_sem(void)
{
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/end");
	sem_unlink("/philo_died");
}

void	end_dinner(int final)
{
	t_gazer	*beholder;

	beholder = get_observer();
	if (beholder->forks)
		sem_close(beholder->forks);
	if (beholder->print)
		sem_close(beholder->print);
	if (beholder->end)
		sem_close(beholder->end);
	free_gazer(beholder);
	if (final)
		clear_sem();
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
