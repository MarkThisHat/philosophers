/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nihilism.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 11:41:33 by maalexan          #+#    #+#             */
/*   Updated: 2023/10/13 21:37:49 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	clear_sem(void)
{
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/end");
	sem_unlink("/philo_done");
}

t_gazer	*get_observer(void)
{
	static t_gazer	beholder;

	return (&beholder);
}

int	main(int argc, char **argv)
{
	if (!validate_args(argc, argv))
		return (1);
	clear_sem();
	if (!set_philosophers(argc, argv))
		return (1);
	forking_it(get_observer());
	end_dinner(42);
}

/*
**	Nihilism:
**	The philosophical view that the world, 
**	and especially human existence, is without 
**	meaning, purpose, comprehensible truth, or 
**	essential value
*/
