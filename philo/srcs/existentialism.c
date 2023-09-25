/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   existentialism.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 16:06:47 by maalexan          #+#    #+#             */
/*   Updated: 2023/09/25 20:17:22 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	have_dinner(t_phil *phil, int rate)
{
	int		holdup;
	t_gazer	*obs;

	obs = get_observer();
	holdup = (obs->highest - get_time_left(phil, obs->die) / rate) * rate;
	printf("I'll hold the fork for %i microsecs\n", holdup);
	usleep(rate * 3);
	holdup = (obs->highest - get_time_left(phil, obs->die) / rate) * rate;
	printf("I'll hold the fork for %i microsecs\n", holdup);
	usleep(rate * 3);
	holdup = (obs->highest - get_time_left(phil, obs->die) / rate) * rate;
	printf("I'll hold the fork for %i microsecs\n", holdup);
	usleep(rate * 3);
	holdup = (obs->highest - get_time_left(phil, obs->die) / rate) * rate;
	printf("I'll hold the fork for %i microsecs\n", holdup);
	usleep(rate * 3);
	holdup = (obs->highest - get_time_left(phil, obs->die) / rate) * rate;
	printf("I'll hold the fork for %i microsecs\n", holdup);
	usleep(rate * 3);
	holdup = (obs->highest - get_time_left(phil, obs->die) / rate) * rate;
	printf("I'll hold the fork for %i microsecs\n", holdup);
}
