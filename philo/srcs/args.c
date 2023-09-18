/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 11:42:56 by maalexan          #+#    #+#             */
/*   Updated: 2023/09/18 15:25:27 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static size_t	ft_strlen(const char *src)
{
	size_t	len;

	if (!src)
		return (0);
	len = 0;
	while (src[len])
		len++;
	return (len);
}

static void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}

static int	invalid_arguments(char *program_name)
{
	ft_putstr_fd("Usage: ", STDERR_FILENO);
	ft_putstr_fd(program_name, STDERR_FILENO);
	ft_putstr_fd(" <number of philosophers> ", STDERR_FILENO);
	ft_putstr_fd("<time to die> ", STDERR_FILENO);
	ft_putstr_fd("<time to eat> ", STDERR_FILENO);
	ft_putstr_fd("<time to sleep> ", STDERR_FILENO);
	ft_putstr_fd("<[number of times each philosopher ", STDERR_FILENO);
	ft_putstr_fd("must eat] - (optional)>\n", STDERR_FILENO);
	return (0);
}

int	validate_args(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (invalid_arguments(argv[0]));
	return (42);
}
