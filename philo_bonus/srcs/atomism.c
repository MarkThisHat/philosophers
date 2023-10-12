/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atomism.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 10:59:07 by maalexan          #+#    #+#             */
/*   Updated: 2023/10/12 11:18:00 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

time_t	get_time_micro(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time_t)time.tv_sec * 1000000ULL + time.tv_usec);
}

time_t	get_time_mili(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time_t)time.tv_sec * 1000ULL + time.tv_usec / 1000);
}

time_t	get_time_current(time_t last_meal)
{
	return (get_time_micro() - last_meal);
}

int	get_time_left(t_phil *phil, time_t die)
{
	return ((int)(die - get_time_current(phil->last_meal)));
}

/*
**	Atomism:
**	The theory that all objects in the Universe are composed 
**	of very small, indestructible elements called atoms. 
**	Buddhists also have well-developed theories of atomism, 
**	which involve momentary, or non-eternal, atoms, 
**	that flash in and out of existence).
*/
