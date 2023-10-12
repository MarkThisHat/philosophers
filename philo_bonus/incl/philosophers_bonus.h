/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 11:27:29 by maalexan          #+#    #+#             */
/*   Updated: 2023/10/12 16:40:37 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# include <fcntl.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

typedef int					t_bool;
typedef unsigned int		t_uint;

typedef enum e_sem
{
	OVER,
	DEAD,
	EAT,
	SLEEP,
	THINK
}	t_sem;

typedef struct s_phil
{
	int				id;
	_Atomic int		meals_left;
	_Atomic t_bool	simulating;
	_Atomic time_t	last_meal;
}					t_phil;

typedef struct s_gazer
{
	t_phil		**philos;
	sem_t		*print;
	sem_t		*forks;
	pthread_t	thread;
	t_uint		highest;
	time_t		die;
	time_t		eat;
	time_t		rest;
	time_t		meals;
}				t_gazer;

# define TRUE 42
# define FALSE 0
# define END 8
# define MAX_PHIL 200
# define MAX_SET 4294967295
# define STR_USAGE " <number of philosophers> \
<time to die> \
<time to eat> \
<time to sleep> \
<[number of times each philosopher must eat] (optional)>\n"
# define STR_MUTEX_CREATE  "Failed to create mutex\n"
# define STR_MUTEX_DESTROY "Failed to destroy mutex\n"
# define STR_FORK "%li %i has taken a fork\n"
# define STR_EAT "%li %i is eating\n"
# define STR_SLEEP "%li %i is sleeping\n"
# define STR_THINK "%li %i is thinking\n"
# define STR_DEAD "%li %i died\n"

t_gazer	*get_observer(void);
t_bool	set_philosophers(int argc, char **argv);
t_bool	validate_args(int argc, char **argv);
void	ft_putstr_fd(char *s, int fd);
size_t	ft_strlen(const char *src);
time_t	ft_atoul(const char *str);
t_bool	ft_isdigit(int c);
time_t	get_time_micro(void);
time_t	get_time_mili(void);
time_t	get_time_current(time_t last_meal);
int		get_time_left(t_phil *phil, time_t die);
void	end_dinner(void);
void	leave_table(int	code);
#endif

/*
**	Allowed external functions:
**	memset, printf, malloc, free, write, fork, kill,
**	exit, pthread_create, pthread_detach, pthread_join,
**	usleep, gettimeofday, waitpid, sem_open, sem_close,
**	sem_post, sem_wait, sem_unlink
*/
