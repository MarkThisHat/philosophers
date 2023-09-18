/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 11:27:29 by maalexan          #+#    #+#             */
/*   Updated: 2023/09/18 15:52:38 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef enum e_state
{
	DEAD,
	EATING,
	SLEEPING,
	THINKING
}	t_state;

typedef struct s_phil
{
	int	number;
	int	state;
	int	forks;
}	t_phil;

int	validate_args(int argc, char **argv);

#endif

/*
**	Allowed external functions:
**	memset, printf, malloc, free, write,
**	usleep, gettimeofday, pthread_create,
**	pthread_detach, pthread_join, pthread_mutex_init,
**	pthread_mutex_destroy, pthread_mutex_lock,
**	pthread_mutex_unlock
*/