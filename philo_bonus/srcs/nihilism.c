/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nihilism.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 11:41:33 by maalexan          #+#    #+#             */
/*   Updated: 2023/10/13 16:41:36 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

t_gazer	*get_observer(void)
{
	static t_gazer	beholder;

	return (&beholder);
}

int	main(int argc, char **argv)
{
	if (!validate_args(argc, argv))
		return (1);
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
