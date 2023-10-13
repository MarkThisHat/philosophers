/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fatalism.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 11:35:05 by maalexan          #+#    #+#             */
/*   Updated: 2023/10/13 16:45:16 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	*wait_child(void *arg)
{
	t_uint	i;
	t_gazer	*beholder;

	i = -1;
	beholder = (t_gazer *)arg;
	sem_wait(beholder->philo->done);
	while (++i < beholder->highest)
		kill(beholder->pids[i], SIGSTOP);
	i = -1;
	while (++i < beholder->highest)
		sem_post(beholder->end);
	i = -1;
	while (++i < beholder->highest)
		kill(beholder->pids[i], SIGCONT);
	pthread_join(beholder->thread[0], NULL);
	return (NULL);
}

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
	int proceed;
	t_uint  i;

	i = -1;
	proceed = 0;
	while (++i < beholder->highest)
		beholder->pids[i] = 0;
	i = 0;
	beholder->philo->last_meal = get_time_micro() + 1000;
	while (i < beholder->highest)
	{
		beholder->pids[i] = fork();
		if (beholder->pids[i] < 0)
			return (FALSE);
		else if (beholder->pids[i] > 0)
			threads_of_fate(beholder, i + 1);
		i++;
	
	}
	pthread_create(&beholder->thread[0], NULL, wait_child, beholder);
//	pthread_create(beholder->thread[1], NULL, wait_philo, beholder);
	while (!proceed)
		proceed = wait_all(beholder->pids, beholder->highest);
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
