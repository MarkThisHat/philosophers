/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nihilism.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 11:41:33 by maalexan          #+#    #+#             */
/*   Updated: 2023/10/12 17:54:28 by maalexan         ###   ########.fr       */
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
	int	end;
end=1;
	if (!validate_args(argc, argv))
		return (1);
	if (!set_philosophers(argc, argv))
		return (1);
//	end = threads_of_fate(get_observer());
	end_dinner(42);
	return (end);
}

/*
**	Nihilism:
**	The philosophical view that the world, 
**	and especially human existence, is without 
**	meaning, purpose, comprehensible truth, or 
**	essential value
*/
