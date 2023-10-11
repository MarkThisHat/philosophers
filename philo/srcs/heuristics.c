/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heuristics.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 22:17:12 by maalexan          #+#    #+#             */
/*   Updated: 2023/10/11 12:59:03 by maalexan         ###   ########.fr       */
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

time_t	ft_atoul(const char *str)
{
	time_t	n;

	n = 0;
	while (ft_isdigit(*str))
		n = 10 * n + (*str++ - '0');
	return (n);
}

void	ft_swap(int *a, int *b)
{
	int	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}
