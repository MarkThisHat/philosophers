/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 21:53:59 by maalexan          #+#    #+#             */
/*   Updated: 2023/09/22 22:21:16 by maalexan         ###   ########.fr       */
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

static t_bool	set_the_table(t_gazer *beholder, t_uint amount)
{
	t_uint	i;

	i = 0;
	while (i < amount)
	{
		beholder->forks[i] = malloc(sizeof(int));
		if (!beholder->forks[i])
		{
			clear_guests(beholder, 0);
			return (clear_cutlery(beholder, i));
		}
		*beholder->forks[i] = i + 1;
		i++;
	}
	return (TRUE);
}

static t_bool	set_guests(t_gazer *beholder, int amount)
{
	int	i;

	i = -1;
	while (++i < amount)
	{
		beholder->philos[i] = malloc(sizeof(t_phil));
		if (!beholder->philos[i])
			return (clear_guests(beholder, i));
		*beholder->philos[i] = (t_phil){0};
	}
	return (TRUE);
}

t_bool	set_philosophers(int argc, char **argv)
{
	t_gazer	*beholder;

	beholder = get_observer();
	if (!set_params(beholder, argc, argv))
		return (FALSE);
	beholder->philos = malloc(sizeof(t_phil *) * beholder->highest);
	if (!beholder->philos)
		return (FALSE);
	beholder->forks = malloc(sizeof(int *) * beholder->highest);
	if (!beholder->forks)
	{
		free(beholder->philos);
		return (FALSE);
	}
	if (!set_guests(beholder, beholder->highest))
		return (free_gazer(beholder));
	if (!set_the_table(beholder, beholder->highest))
		return (free_gazer(beholder));
	for (t_uint i = 0; i < beholder->highest; i++)
	{
		if (beholder->philos[i])
			printf("philo %i\n", i + 1);
		if (beholder->forks[i])
			printf("fork %i\n", *beholder->forks[i]);
	}
	printf("Die: %lli\nEat: %lli\nSleep: %lli\nMeals %lli\n", beholder->die, beholder->eat, beholder->rest, beholder->meals);
	end_dinner();
	return (TRUE);
}
