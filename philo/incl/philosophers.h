/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 11:27:29 by maalexan          #+#    #+#             */
/*   Updated: 2023/10/07 14:44:12 by maalexan         ###   ########.fr       */
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

typedef int					t_bool;
typedef unsigned int		t_uint;

typedef enum e_state
{
	DEAD,
	EATING,
	SLEEPING,
	THINKING
}	t_state;

typedef struct s_phil
{
	int				id;
	_Atomic int		state;
	_Atomic int		meals_left;
	_Atomic time_t	last_meal;
	int				first_fork;
	int				second_fork;
	int				held_forks;
}					t_phil;

typedef struct s_gazer
{
	t_phil			**philos;
	pthread_t		*threads;
	pthread_mutex_t	printer;
	pthread_mutex_t	*mutexes;
	_Atomic t_bool	simulating;
	t_uint			highest;
	time_t			die;
	time_t			eat;
	time_t			rest;
	time_t			meals;
}					t_gazer;

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
t_bool	simulating(void);
t_bool	validate_args(int argc, char **argv);
void	ft_putstr_fd(char *s, int fd);
size_t	ft_strlen(const char *src);
time_t	ft_atoul(const char *str);
t_bool	ft_isdigit(int c);
time_t	get_time_micro(void);
time_t	get_time_mili(void);
time_t	get_time_current(time_t last_meal);
int		get_time_left(t_phil *phil, time_t die);
void	forks_priority(t_phil *phil, int left, int right);
t_bool	set_philosophers(int argc, char **argv);
t_bool	clear_guests(t_gazer *beholder, int max);
t_bool	free_gazer(t_gazer *beholder);
int		threads_of_fate(t_gazer *beholder);
t_bool	start_threading(t_gazer *beholder);
t_bool	finish_threading(t_gazer *beholder, int max);
void	end_dinner(void);
t_bool	lock_mutex(t_phil *phil, pthread_mutex_t *mutexes, int index);
t_bool	unlock_mutex(pthread_mutex_t *mutexes, int index);
t_bool	printer(char *str, int id);
void	*have_dinner(void *arg);
void	*oversee_dinner(void *arg);

#endif

/*
**	Allowed external functions:
**	memset, printf, malloc, free, write,
**	usleep, gettimeofday, pthread_create,
**	pthread_detach, pthread_join, pthread_mutex_init,
**	pthread_mutex_destroy, pthread_mutex_lock,
**	pthread_mutex_unlock
*/
