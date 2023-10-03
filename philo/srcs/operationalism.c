/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operationalism.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:08:42 by maalexan          #+#    #+#             */
/*   Updated: 2023/10/03 17:17:44 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_bool	printer(char *str, int id)
{
	if (!simulating())
		return (FALSE);
	if (!pthread_mutex_lock(&get_observer()->printer))
		printf(str, get_time_mili(), id);
	else
		return (FALSE);
	if (!pthread_mutex_unlock(&get_observer()->printer))
		return (TRUE);
	return (FALSE);
}

t_bool	unlock_mutex(pthread_mutex_t *mutexes, int index)
{
	if (!pthread_mutex_unlock(&mutexes[index]))
	{
		get_observer()->simulating = END;
		return (FALSE);
	}
	return (TRUE);
}

t_bool	lock_mutex(t_phil *phil, pthread_mutex_t *mutexes, int index)
{
	if (!simulating())
		return (FALSE);
	if (!pthread_mutex_lock(&mutexes[index]))
		printer(STR_FORK, phil->id);
	return (TRUE);
}
