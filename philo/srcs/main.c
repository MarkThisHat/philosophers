/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 11:41:33 by maalexan          #+#    #+#             */
/*   Updated: 2023/09/20 22:38:11 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

unsigned int	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec % 1000 * 1000000 + time.tv_usec);
}

int	main(int argc, char **argv)
{
//	t_phil	**philosophers;

	if (!validate_args(argc, argv))
		return (1);
	printf("Get time: %i\n", get_time());
	printf("Get time2: %i\n", get_time());
	printf("Get time3: %i\n", get_time());
}
