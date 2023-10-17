/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pluralism.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 22:35:25 by maalexan          #+#    #+#             */
/*   Updated: 2023/10/17 20:23:25 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

/*
**	Parent
*/
void	*wait_child(void *arg)
{
	t_uint	i;
	t_gazer	*beholder;

	usleep(900);
	i = -1;
	beholder = (t_gazer *)arg;
	sem_wait(beholder->philo.done);
	while (++i < beholder->highest)
		kill(beholder->pids[i], SIGSTOP);
	i = -1;
	while (++i < beholder->highest)
		sem_post(beholder->end);
	i = -1;
	while (++i < beholder->highest)
		kill(beholder->pids[i], SIGCONT);
	return (NULL);
}

/*
**	Parent
*/
int	wait_all(pid_t *pids, int max)
{
	int	i;
	int	status;

	i = -1;
	while (++i < max)
		if (pids[i] > 0)
			waitpid(pids[i], &status, 0);
	return (TRUE);
}

int	forking_it(t_gazer *beholder)
{
	t_uint	i;
	int		proceed;

	i = -1;
	proceed = 0;
	while (++i < beholder->highest)
		beholder->pids[i] = 0;
	i = 0;
	beholder->philo.last_meal = get_time_micro() + 1000;
	while (i < beholder->highest)
	{
		beholder->pids[i] = fork();
		if (beholder->pids[i] < 0)
			return (FALSE);
		else if (beholder->pids[i] == 0)
			threads_of_fate(beholder, i + 1);
		i++;
	}
	pthread_create(&beholder->thread[0], NULL, wait_child, beholder);
	while (!proceed)
		proceed = wait_all(beholder->pids, beholder->highest);
	pthread_join(beholder->thread[0], NULL);
	return (0);
}

/*
**	In the area of philosophy of the mind, distinguishes a position
**	where one believes there to be ultimately many kinds of substances
**	in the world, as opposed to monism and dualism.
*/
