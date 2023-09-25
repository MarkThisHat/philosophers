/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fatalism.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 11:35:05 by maalexan          #+#    #+#             */
/*   Updated: 2023/09/25 20:12:45 by maalexan         ###   ########.fr       */
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

void	threads_of_fate(t_gazer *beholder)
{
	int	base_beat;

	base_beat = beholder->die / beholder->highest;
	beholder->pulse = get_time_micro();
	diffuse_time(beholder->philos, beholder->pulse, beholder->highest);
/*	for (t_uint i = 0; i < beholder->highest; i++)
	{
		printf("Philo %i has fork %i to the left and fork %i to the right\n", \
		beholder->philos[i]->id, *beholder->philos[i]->right_fork, \
		*beholder->philos[i]->left_fork);
		printf("It has the timestamp of %lli\n", beholder->philos[i]->last_meal);
	}*/
	have_dinner(beholder->philos[0], base_beat);
}
