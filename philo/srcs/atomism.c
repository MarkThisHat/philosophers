/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atomism.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 10:59:07 by maalexan          #+#    #+#             */
/*   Updated: 2023/09/25 16:23:26 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_ullong	get_time_micro(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((t_ullong)time.tv_sec * 1000000ULL + time.tv_usec);
}

t_ullong	get_time_mili(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((t_ullong)time.tv_sec * 1000ULL + time.tv_usec / 1000);
}

t_ullong	get_time_current(t_ullong last_meal)
{
	return (get_time_micro() - last_meal);
}

int	get_time_left(t_phil *phil, t_ullong die)
{
	return ((int)(die - get_time_current(phil->last_meal)));
}
