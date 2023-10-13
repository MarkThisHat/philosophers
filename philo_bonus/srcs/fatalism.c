/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fatalism.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 11:35:05 by maalexan          #+#    #+#             */
/*   Updated: 2023/10/13 13:14:07 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	forking_it(t_gazer *beholder)
{
	t_uint  i;

    i = 0;
    beholder->philos->last_meal = get_time_micro() + 1000;
    while (i < beholder->highest)
    {
        beholder->pid[i] = fork();
        if (beholder->pid[i] < 0)
            return (FALSE);
        else if (beholder->pid[i])
    }
	usleep(100);
	return (TRUE);
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
