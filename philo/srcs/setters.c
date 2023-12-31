/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 21:53:59 by maalexan          #+#    #+#             */
/*   Updated: 2023/10/15 23:17:15 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_bool	set_params(t_gazer *beholder, int argc, char **argv)
{
	time_t	die;
	time_t	eat;
	time_t	rest;
	time_t	meals;

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

static t_bool	set_the_table(t_gazer *beholder, int amount)
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

static void	set_philosophers_stats(t_gazer *beholder, t_uint amount)
{
	t_uint	i;
	int		left;
	int		right;

	i = 0;
	while (i < amount)
	{
		right = i;
		if (i)
			left = i - 1;
		else
			left = amount - 1;
		beholder->philos[i]->id = i + 1;
		beholder->philos[i]->state = THINKING;
		forks_priority(beholder->philos[i], left, right);
		i++;
	}
}

static t_bool	set_threads(t_gazer *beholder)
{
	beholder->threads = malloc(sizeof(pthread_t) * (beholder->highest + 1));
	if (!beholder->threads)
		return (FALSE);
	beholder->mutexes = malloc(sizeof(pthread_mutex_t) * beholder->highest);
	if (!beholder->mutexes)
	{
		free(beholder->threads);
		return (FALSE);
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
	if (!set_threads(beholder))
		return (free_gazer(beholder));
	if (!set_the_table(beholder, beholder->highest))
		return (free_gazer(beholder));
	set_philosophers_stats(beholder, beholder->highest);
	return (TRUE);
}
