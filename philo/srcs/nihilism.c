/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nihilism.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 11:41:33 by maalexan          #+#    #+#             */
/*   Updated: 2023/09/27 21:08:42 by maalexan         ###   ########.fr       */
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
/*	printf("Get time micro: %lli\n", get_time_micro());
	printf("Get time mili 2: %lli\n", get_time_mili());
	printf("Get time mili 3: %lli\n", get_time_mili()); */
	end = threads_of_fate(get_observer());
	end_dinner();
	return (end);
}

/*
for (t_uint i = 0; i < beholder->highest; i++)
	{
		if (beholder->philos[i])
			printf("philo %i\n", i + 1);
		if (beholder->forks[i])
			printf("fork %i\n", *beholder->forks[i]);
	}
	printf("Die: %lli\nEat: %lli\nSleep: %lli\nMeals %lli\n", \
	beholder->die, beholder->eat, beholder->rest, beholder->meals);
	for (t_uint i = 0; i < beholder->highest; i++)
	{
		printf("Philo %i has fork %i to the left and fork %i to the right\n", \
		beholder->philos[i]->id, \*beholder->philos[i]->right_fork, \
		*beholder->philos[i]->left_fork);
	}
	end_dinner();

*/
