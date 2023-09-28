/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heuristics.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 22:17:12 by maalexan          #+#    #+#             */
/*   Updated: 2023/09/27 21:00:15 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t	ft_strlen(const char *src)
{
	size_t	len;

	if (!src)
		return (0);
	len = 0;
	while (src[len])
		len++;
	return (len);
}

void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}

t_bool	ft_isdigit(int c)
{
	return ((unsigned)c - '0' < 10);
}

t_ullong	ft_atoul(const char *str)
{
	t_ullong	n;

	n = 0;
	while (ft_isdigit(*str))
		n = 10 * n + (*str++ - '0');
	return (n);
}

void	set_cutlery(int *first, int *second, int *left, int *right)
{
	if (*left < *right)
	{
		*first = *left;
		*second = *right;
	}
	else
	{
		*first = *right;
		*second = *left;
	}
}
