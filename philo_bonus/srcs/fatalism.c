/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fatalism.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 11:35:05 by maalexan          #+#    #+#             */
/*   Updated: 2023/10/12 11:25:07 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	diffuse_time(t_phil **philos, time_t time, t_uint amount)
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
		if (pthread_mutex_destroy(&beholder->mutexes[i]))
			ft_putstr_fd(STR_MUTEX_DESTROY, STDERR_FILENO);
		i++;
	}
	if (pthread_mutex_destroy(&beholder->printer))
		ft_putstr_fd(STR_MUTEX_DESTROY, STDERR_FILENO);
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
	if (pthread_mutex_init(&beholder->printer, NULL))
	{
		ft_putstr_fd(STR_MUTEX_CREATE, STDERR_FILENO);
		return (mutex_clean(beholder, i));
	}
	return (TRUE);
}

int	threads_of_fate(t_gazer *beholder)
{
	if (!mutex_ettiquete(beholder))
		return (1);
	diffuse_time(beholder->philos, get_time_micro(), beholder->highest);
	if (!start_threading(beholder))
		return (1);
	while (TRUE)
	{
		usleep(100);
		if (!simulating())
			break ;
	}
	finish_threading(beholder, beholder->highest + 1);
	mutex_clean(beholder, beholder->highest);
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
