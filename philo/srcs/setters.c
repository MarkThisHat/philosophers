/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 21:53:59 by maalexan          #+#    #+#             */
/*   Updated: 2023/09/21 22:38:23 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_bool	set_params(t_gazer *beholder, int argc, char **argv)
{
	t_ullong	die;
	t_ullong	eat;
	t_ullong	rest;
	t_ullong	meals;

	die = ft_atoul(argv[2]) * 1000;
	eat = ft_atoul(argv[3]) * 1000;
	rest = ft_atoul(argv[4]) * 1000;
	meals = 0;
	if (argc > 5)
		meals = ft_atoul(argv[5]);
	if (die > MAX_SET || eat > MAX_SET || rest > MAX_SET || meals > MAX_SET)
		return (FALSE);
	beholder->die = die;
	beholder->eat = eat;
	beholder->rest = rest;
	beholder->meals = meals;
	return (TRUE);
}

t_bool	set_philosophers(int argc, char **argv)
{
	t_gazer	*beholder;

	beholder = get_observer();
	if (!set_params(beholder, argc, argv))
		return (FALSE);
	printf("Die: %lli\nEat: %lli\nSleep: %lli\nMeals %lli\n", beholder->die, beholder->eat, beholder->rest, beholder->meals);
	return (TRUE);
}
