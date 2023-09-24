/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   existentialism.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 16:06:47 by maalexan          #+#    #+#             */
/*   Updated: 2023/09/24 12:22:24 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	have_dinner(t_gazer *beholder, int base_beat)
{	
	printf("Base beat: %i\n", base_beat);
	printf("Time to die %lli\n", beholder->die);
	printf("Last meal: %lli\n", get_time_current(beholder->philos[0]->last_meal));
}