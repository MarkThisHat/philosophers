/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nihilism.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 11:41:33 by maalexan          #+#    #+#             */
/*   Updated: 2023/10/07 14:55:14 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_gazer	*get_observer(void)
{
	static t_gazer	beholder;

	return (&beholder);
}

t_bool	simulating(void)
{
	return (!get_observer()->simulating);
}

int	main(int argc, char **argv)
{
	int	end;

	if (!validate_args(argc, argv))
		return (1);
	if (!set_philosophers(argc, argv))
		return (1);
	end = threads_of_fate(get_observer());
	end_dinner();
	return (end);
}

/*	printf("Get time micro: %lli\n", get_time_micro());
	printf("Get time mili 2: %lli\n", get_time_mili());
	printf("Get time mili 3: %lli\n", get_time_mili());
for (t_uint i = 0; i < beholder->highest; i++)
	{
		if (beholder->philos[i])
			printf("philo %i\n", i + 1);
	}
	printf("Die: %li\nEat: %li\nSleep: %li\nMeals %li\n", \
	beholder->die, beholder->eat, beholder->rest, beholder->meals);
	for (t_uint i = 0; i < beholder->highest; i++)
	{
		printf("Philo %i has fork %i as first and fork %i as second\n", \
		beholder->philos[i]->id, beholder->philos[i]->first_fork, \
		beholder->philos[i]->second_fork);
	}
	end_dinner();

*/
