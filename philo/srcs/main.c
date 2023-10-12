/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 11:41:33 by maalexan          #+#    #+#             */
/*   Updated: 2023/10/12 11:47:10 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_gazer	*get_observer(void)
{
	static t_gazer	beholder;

	return (&beholder);
}

t_bool	simulating(void)
{
	return (!get_observer()->simulating);
}

int	main(int argc, char **argv)
{
	int	end;

	if (!validate_args(argc, argv))
		return (1);
	if (!set_philosophers(argc, argv))
		return (1);
	end = threads_of_fate(get_observer());
	end_dinner();
	return (end);
}
