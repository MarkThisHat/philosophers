/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   praxis.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 21:53:59 by maalexan          #+#    #+#             */
/*   Updated: 2023/10/12 22:56:42 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

static	t_bool	set_semaphores(t_gazer *beholder)
{
	beholder->forks = sem_open("forks", O_CREAT, S_IRWXU, beholder->highest);
	if (beholder->forks == SEM_FAILED)
		return (FALSE);
	beholder->print = sem_open("print", O_CREAT, S_IRWXU, 1);
	if (beholder->print == SEM_FAILED)
	{
		sem_close(beholder->forks);
		beholder->forks = NULL;
		sem_unlink("forks");
		return (FALSE);
	}
	beholder->end = sem_open("end", O_CREAT, S_IRWXU, 1);
	if (beholder->end == SEM_FAILED)
	{
		sem_close(beholder->forks);
		beholder->forks = NULL;
		sem_unlink("forks");
		sem_close(beholder->print);
		beholder->print = NULL;
		sem_unlink("print");
		return (FALSE);
	}
	return (TRUE);
}

static t_bool	set_params(t_gazer *beholder, int argc, char **argv)
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

	i = 0;
	while (i < amount)
	{
		beholder->philos[i]->id = i + 1;
		beholder->philos[i]->meals_left = get_observer()->meals;
		i++;
	}
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
	beholder->pids = malloc(sizeof(pid_t) * beholder->highest);
	if (!beholder->pids)
		return (free_gazer(beholder));
	if (!set_the_table(beholder, beholder->highest))
		return (free_gazer(beholder));
	if (!set_semaphores(beholder))
		return (free_gazer(beholder));
	set_philosophers_stats(beholder, beholder->highest);
	return (TRUE);
}

/*
**	Praxis is the process by which a theory, lesson, or skill is
**	enacted, embodied, realized, applied, or put into practice.
**	"Praxis" may also refer to the act of engaging, applying,
**	exercising, realizing, or practising ideas.
*/
