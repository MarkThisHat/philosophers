/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hermeneutics.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 21:57:30 by maalexan          #+#    #+#             */
/*   Updated: 2023/10/08 19:48:46 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_bool	over_and_out(t_gazer *beholder)
{
	t_uint	i;

	i = -1;
	while (++i < beholder->highest)
		beholder->philos[i]->state = OVER;
	return (END);
}

t_bool	clear_guests(t_gazer *beholder, int max)
{
	int	i;

	i = 0;
	while (i < max)
		free(beholder->philos[i++]);
	return (FALSE);
}

t_bool	free_gazer(t_gazer *beholder)
{
	free(beholder->philos);
	return (FALSE);
}

void	end_dinner(void)
{
	t_gazer	*beholder;

	beholder = get_observer();
	clear_guests(beholder, beholder->highest);
	free(beholder->threads);
	free(beholder->mutexes);
	free_gazer(beholder);
}
