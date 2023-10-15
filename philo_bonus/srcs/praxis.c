/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   praxis.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 21:53:59 by maalexan          #+#    #+#             */
/*   Updated: 2023/10/15 17:17:22 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

static	t_bool	set_semaphores(t_gazer *beholder)
{
	beholder->forks = sem_open("/forks", O_CREAT, S_IRWXU, beholder->highest);
	if (beholder->forks == SEM_FAILED)
		return (FALSE);
	beholder->print = sem_open("/print", O_CREAT, S_IRWXU, 1);
	if (beholder->print == SEM_FAILED)
		return (FALSE);
	beholder->end = sem_open("/end", O_CREAT, S_IRWXU, beholder->highest);
	if (beholder->end == SEM_FAILED)
		return (FALSE);
	beholder->philo->done = sem_open("/philo_done", \
	O_CREAT, S_IRWXU, beholder->highest);
	if (beholder->philo->done == SEM_FAILED)
		return (FALSE);
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

t_bool	set_philosophers(int argc, char **argv)
{
	t_gazer	*beholder;

	beholder = get_observer();
	if (!set_params(beholder, argc, argv))
		return (FALSE);
	beholder->philo = malloc(sizeof(t_phil));
	if (!beholder->philo)
		return (FALSE);
	*beholder->philo = (t_phil){0};
	beholder->philo->meals_left = beholder->meals;
	beholder->pids = malloc(sizeof(pid_t) * beholder->highest);
	if (!beholder->pids)
		return (free_gazer(beholder));
	if (!set_semaphores(beholder))
		return (free_gazer(beholder));
	return (TRUE);
}

/*
**	Praxis is the process by which a theory, lesson, or skill is
**	enacted, embodied, realized, applied, or put into practice.
**	"Praxis" may also refer to the act of engaging, applying,
**	exercising, realizing, or practising ideas.
*/
