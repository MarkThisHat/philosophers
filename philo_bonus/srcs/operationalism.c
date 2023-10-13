/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operationalism.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:08:42 by maalexan          #+#    #+#             */
/*   Updated: 2023/10/12 23:11:45 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

t_bool	printer(char *str, t_phil *phil)
{
	sem_wait(get_observer()->print);
	if (phil->terminate)
	{
		sem_post(get_observer()->print);
		return (FALSE);
	}
	printf(str, get_time_mili(), phil->id);
	sem_post(get_observer()->print);
	return (TRUE);
}

/*
**	Operationalism:
**	The philosophy of defining a concept as the operations that will
**	measure the concept (variables) through specific observations.
*/
