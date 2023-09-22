/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 21:53:59 by maalexan          #+#    #+#             */
/*   Updated: 2023/09/22 16:55:37 by maalexan         ###   ########.fr       */
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

static t_bool	clear_guests(t_gazer *beholder)
{
	int	i;

	i = 0;
	while (beholder->philos[++i])
		free(beholder->philos[i]);
	return (FALSE);
}

static t_bool	set_the_table(t_gazer *beholder, int amount)
{
	int	i;

	i = -1;
	while (++i < amount)
	{
		beholder->forks[i] = NULL;
		beholder->philos[i] = NULL;
	}
	i = 0;
	while (++i < amount)
	{
		beholder->philos[i] = malloc(sizeof(t_gazer));
		if (!beholder->philos[i])
			return (clear_guests(beholder));
	}
	beholder->philos[0] = malloc(sizeof(char));
	if (!beholder->philos[0])
		return (clear_guests(beholder));
	return (TRUE);
}

t_bool	set_philosophers(int argc, char **argv)
{
	t_gazer	*beholder;

	beholder = get_observer();
	if (!set_params(beholder, argc, argv))
		return (FALSE);
	beholder->philos = malloc(sizeof(void *) * beholder->highest + 1);
	if (!beholder->philos)
		return (FALSE);
	beholder->forks = malloc(sizeof(int *) * beholder->highest);
	if (!beholder->forks)
	{
		free(beholder->philos);
		return (FALSE);
	}
	if (!set_the_table(beholder, beholder->highest + 1))
	{
		free(beholder->philos);
		free(beholder->forks);
		return (FALSE);
	}
	printf("Die: %lli\nEat: %lli\nSleep: %lli\nMeals %lli\n", beholder->die, beholder->eat, beholder->rest, beholder->meals);
	return (TRUE);
}
