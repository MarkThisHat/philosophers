/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pluralism.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 22:35:25 by maalexan          #+#    #+#             */
/*   Updated: 2023/10/08 18:17:46 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static time_t	time_of_death(t_phil *philo, time_t die)
{
	return (philo->last_meal + die);
}

t_bool	over_and_out(t_gazer *beholder)
{
	t_uint	i;

	i = -1;
	while (++i < beholder->highest)
		beholder->philos[i]->state = OVER;
	return (END);
}

static t_bool	loop_simulation(t_gazer *beholder)
{
	t_uint	i;
	time_t	demise;

	i = 0;
	while (i < beholder->highest)
	{
		demise = time_of_death(beholder->philos[i], beholder->die);
		if (beholder->meals && !beholder->philos[i]->meals_left)
		{
			beholder->simulating = over_and_out(beholder);
			return (FALSE);
		}
		else if (get_time_micro() > demise)
		{
			printer(STR_DEAD, beholder->philos[i]->id);
			beholder->simulating = over_and_out(beholder);
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

void	*oversee_dinner(void *arg)
{
	t_bool	carry_on;

	carry_on = 1;
	while (carry_on)
	{
		usleep(100);
		carry_on = loop_simulation((t_gazer *)arg);
	}
	return (NULL);
}

t_bool	finish_threading(t_gazer *beholder, int max)
{
	int	i;

	i = -1;
	while (++i < max)
		pthread_join(beholder->threads[i], NULL);
	return (FALSE);
}

t_bool	start_threading(t_gazer *beholder)
{
	t_uint		i;
	t_uint		max;
	t_phil		**phil;
	pthread_t	*threads;

	max = beholder->highest + 1;
	threads = beholder->threads;
	phil = beholder->philos;
	i = 0;
	while (i < max - 1)
	{
		if (pthread_create(&threads[i], NULL, have_dinner, phil[i]))
			return (finish_threading(beholder, i));
		i++;
	}
	if (pthread_create(&threads[i], NULL, oversee_dinner, beholder))
		return (finish_threading(beholder, i));
	return (TRUE);
}
