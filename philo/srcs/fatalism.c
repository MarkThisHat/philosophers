/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fatalism.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 11:35:05 by maalexan          #+#    #+#             */
/*   Updated: 2023/09/27 22:42:11 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	diffuse_time(t_phil **philos, t_ullong time, t_uint amount)
{
	t_uint	i;

	i = 0;
	while (i < amount)
		philos[i++]->last_meal = time;
}

static t_bool	mutex_clean(t_gazer *beholder, t_uint max)
{
	t_uint	i;

	i = 0;
	while (i < max)
	{
		if (pthread_mutex_destroy(&beholder->mutexes[i++]))
			ft_putstr_fd(STR_MUTEX_DESTROY, STDERR_FILENO);
	}
	return (FALSE);
}

static t_bool	mutex_ettiquete(t_gazer *beholder)
{
	t_uint	i;

	i = 0;
	while (i < beholder->highest)
	{
		if (pthread_mutex_init(&beholder->mutexes[i], NULL))
		{
			ft_putstr_fd(STR_MUTEX_CREATE, STDERR_FILENO);
			return (mutex_clean(beholder, i));
		}
		i++;
	}
	return (TRUE);
}

int	threads_of_fate(t_gazer *beholder)
{
	if (!mutex_ettiquete(beholder))
		return (1);
	diffuse_time(beholder->philos, get_time_micro(), beholder->highest);
/*	for (t_uint i = 0; i < beholder->highest; i++)
	{
		printf("Philo %i has fork %i to the left and fork %i to the right\n", \
		beholder->philos[i]->id, *beholder->philos[i]->right_fork, \
		*beholder->philos[i]->left_fork);
		printf("It has the timestamp of %lli\n", beholder->philos[i]->last_meal);
	}*/
	have_dinner(beholder->philos[3], beholder);
	mutex_clean(beholder, beholder->highest);
	return (0);
}
