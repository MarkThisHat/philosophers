/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 11:27:29 by maalexan          #+#    #+#             */
/*   Updated: 2023/09/27 22:32:27 by maalexan         ###   ########.fr       */
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
typedef unsigned long long	t_ullong;

typedef enum e_state
{
	DEAD,
	EATING,
	SLEEPING,
	THINKING
}	t_state;

typedef struct s_phil
{
	int					id;
	int					state;
	int					meals_left;
	_Atomic t_ullong	last_meal;
	int					*left_fork;
	int					*right_fork;
}						t_phil;

typedef struct s_gazer
{
	t_phil			**philos;
	int				*forks;
	pthread_mutex_t	*mutexes;
	_Atomic t_bool	simulating;
	t_uint			highest;
	t_ullong		die;
	t_ullong		eat;
	t_ullong		rest;
	t_ullong		meals;
	t_ullong		pulse;
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
# define STR_MUTEX_LOCK  "Failed to lock/unlock mutex\n"
# define STR_MUTEX_DESTROY "Failed to destroy mutex\n"

t_gazer		*get_observer(void);
t_bool		simulating(void);
t_bool		validate_args(int argc, char **argv);
void		ft_putstr_fd(char *s, int fd);
size_t		ft_strlen(const char *src);
t_ullong	ft_atoul(const char *str);
t_bool		ft_isdigit(int c);
t_ullong	get_time_micro(void);
t_ullong	get_time_mili(void);
t_ullong	get_time_current(t_ullong last_meal);
int			get_time_left(t_phil *phil, t_ullong die);
void		set_cutlery(int *first, int *second, int *left, int *right);
t_bool		set_philosophers(int argc, char **argv);
t_bool		clear_guests(t_gazer *beholder, int max);
t_bool		free_gazer(t_gazer *beholder);
int			threads_of_fate(t_gazer *beholder);
void		end_dinner(void);

void		have_dinner(t_phil *phil, t_gazer *beholder);

#endif

/*
**	Allowed external functions:
**	memset, printf, malloc, free, write,
**	usleep, gettimeofday, pthread_create,
**	pthread_detach, pthread_join, pthread_mutex_init,
**	pthread_mutex_destroy, pthread_mutex_lock,
**	pthread_mutex_unlock
*/
