/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   existentialism.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 16:06:47 by maalexan          #+#    #+#             */
/*   Updated: 2023/09/25 20:14:32 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
void	have_dinner(t_phil *phil, int rate)
{
	int		holdup;
	t_gazer	*obs;

	obs = get_observer();
	holdup = (obs->highest - get_time_left(phil, obs->die) / rate) * rate;
	printf("I'll hold the fork for %i microsecs\n", holdup);
}

/*
void	have_dinner(t_gazer *beholder, int base_beat)
{	
	printf("Base beat: %i\n", base_beat);
	printf("Time to die %lli\n", beholder->die);
	printf("Last meal: %lli\n", get_time_current(beholder->philos[0]->last_meal));
	printf("Time alive left: %i\n", (int)(beholder->die - get_time_current(beholder->philos[0]->last_meal)));
	usleep(base_beat);
	printf("Last meal: %lli\n", get_time_current(beholder->philos[0]->last_meal));
	printf("Time alive left: %i\n", (int)(beholder->die - get_time_current(beholder->philos[0]->last_meal)));
	usleep(base_beat);
	printf("Last meal: %lli\n", get_time_current(beholder->philos[0]->last_meal));
	printf("Time alive left: %i\n", (int)(beholder->die - get_time_current(beholder->philos[0]->last_meal)));
	usleep(base_beat);
	printf("Last meal: %lli\n", get_time_current(beholder->philos[0]->last_meal));
	printf("Time alive left: %i\n", (int)(beholder->die - get_time_current(beholder->philos[0]->last_meal)));
	usleep(base_beat);
	printf("Last meal: %lli\n", get_time_current(beholder->philos[0]->last_meal));
	printf("Time alive left: %i\n", (int)(beholder->die - get_time_current(beholder->philos[0]->last_meal)));
	usleep(base_beat);
	printf("Last meal: %lli\n", get_time_current(beholder->philos[0]->last_meal));
	printf("Time alive left: %i\n", (int)(beholder->die - get_time_current(beholder->philos[0]->last_meal)));
	usleep(base_beat);
	printf("Last meal: %lli\n", get_time_current(beholder->philos[0]->last_meal));
	printf("Time alive left: %i\n", (int)(beholder->die - get_time_current(beholder->philos[0]->last_meal)));
	usleep(base_beat);
	printf("Last meal: %lli\n", get_time_current(beholder->philos[0]->last_meal));
	printf("Time alive left: %i\n", (int)(beholder->die - get_time_current(beholder->philos[0]->last_meal)));


	"Better" version:
	(number_of_philosophers - (death_time - current_time - last_meal) / (death_time / number_of_philosophers)) * (death_time / number_of_philosophers)
	printf("Base beat: %i\n", base_beat);
	printf("Time alive left: %i\n", get_time_left(phil, die));
	printf("numb %i\n", get_observer()->highest - get_time_left(phil, die) / base_beat);
	printf("I'll hold the fork for %i microsecs\n", (get_observer()->highest - get_time_left(phil, die) / base_beat) * base_beat);
	usleep(base_beat);
	printf("Time alive left: %i\n", get_time_left(phil, die));
	printf("numb %i\n", get_observer()->highest - get_time_left(phil, die) / base_beat);
	printf("I'll hold the fork for %i microsecs\n", (get_observer()->highest - get_time_left(phil, die) / base_beat) * base_beat);
	usleep(base_beat);
	printf("Time alive left: %i\n", get_time_left(phil, die));
	printf("numb %i\n", get_observer()->highest - get_time_left(phil, die) / base_beat);
	printf("I'll hold the fork for %i microsecs\n", (get_observer()->highest - get_time_left(phil, die) / base_beat) * base_beat);
	usleep(base_beat);
	printf("Time alive left: %i\n", get_time_left(phil, die));
	printf("numb %i\n", get_observer()->highest - get_time_left(phil, die) / base_beat);
	printf("I'll hold the fork for %i microsecs\n", (get_observer()->highest - get_time_left(phil, die) / base_beat) * base_beat);
	usleep(base_beat);
	printf("Time alive left: %i\n", get_time_left(phil, die));
	printf("numb %i\n", get_observer()->highest - get_time_left(phil, die) / base_beat);
	printf("I'll hold the fork for %i microsecs\n", (get_observer()->highest - get_time_left(phil, die) / base_beat) * base_beat);
	usleep(base_beat);
	printf("Time alive left: %i\n", get_time_left(phil, die));
	printf("numb %i\n", get_observer()->highest - get_time_left(phil, die) / base_beat);
	printf("I'll hold the fork for %i microsecs\n", (get_observer()->highest - get_time_left(phil, die) / base_beat) * base_beat);
	usleep(base_beat);
	printf("Time alive left: %i\n", get_time_left(phil, die));
	printf("numb %i\n", get_observer()->highest - get_time_left(phil, die) / base_beat);

	printf("I'll hold the fork for %i microsecs\n", (obs->highest - get_time_left(phil, obs->die) / rate) * rate);
	printf("Same, but with var %i\n", wait);
	usleep(rate * 2);
	wait = (obs->highest - get_time_left(phil, obs->die) / rate) * rate;
	printf("I'll hold the fork for %i microsecs\n", (obs->highest - get_time_left(phil, obs->die) / rate) * rate);
	printf("Same, but with var %i\n", wait);
	usleep(rate * 2);
	wait = (obs->highest - get_time_left(phil, obs->die) / rate) * rate;
	printf("I'll hold the fork for %i microsecs\n", (obs->highest - get_time_left(phil, obs->die) / rate) * rate);
	printf("Same, but with var %i\n", wait);
	usleep(rate * 2);
	wait = (obs->highest - get_time_left(phil, obs->die) / rate) * rate;
	printf("I'll hold the fork for %i microsecs\n", (obs->highest - get_time_left(phil, obs->die) / rate) * rate);
	printf("Same, but with var %i\n", wait);
}
*/