/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 11:41:33 by maalexan          #+#    #+#             */
/*   Updated: 2023/09/21 22:27:46 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_gazer	*get_observer(void)
{
	static t_gazer	beholder;

	return (&beholder);
}

t_ullong	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((t_ullong)time.tv_sec * 1000000 + time.tv_usec);
}

int	main(int argc, char **argv)
{
	if (!validate_args(argc, argv))
		return (1);
	if (!set_philosophers(argc, argv))
		return (1);
	printf("Get time: %lli\n", get_time());
	printf("Get time2: %lli\n", get_time());
	printf("Get time3: %lli\n", get_time());
}
