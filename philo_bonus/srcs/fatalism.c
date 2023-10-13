/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fatalism.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 11:35:05 by maalexan          #+#    #+#             */
/*   Updated: 2023/10/12 23:18:16 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

static void	diffuse_time(t_phil **philos, time_t time, t_uint amount)
{
	t_uint	i;

	i = 0;
	while (i < amount)
		philos[i++]->last_meal = time;
}

int	threads_of_fate(t_gazer *beholder)
{
	diffuse_time(beholder->philos, get_time_micro(), beholder->highest);
	while (TRUE)
	{
		usleep(100);
		break ;
	}
	return (0);
}

/*
**	Fatalism:
**	The view that human deliberation and actions are pointless
**	and ineffectual in determining events, because whatever will
**	be will be. One ancient argument, called the idle argument,
**	went like this: "If it is fated for you to recover from your
**	illness, then you will recover whether you call a doctor or not.
**	Likewise, if you are fated not to recover, you will not do so even
**	if you call a doctor. So, calling a doctor makes no difference."
**	Arguments like this are usually rejected even by causal determinists,
**	who may say that it may be determined that only a doctor can cure you.
*/
