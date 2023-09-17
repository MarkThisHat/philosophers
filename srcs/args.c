/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 11:42:56 by maalexan          #+#    #+#             */
/*   Updated: 2023/09/17 11:58:18 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	invalid_arguments(char *program_name)
{
	ft_putstr_fd("Usage: ", STDERR_FILENO);
	ft_putstr_fd(program_name, STDERR_FILENO);
	ft_putstr_fd(" <number of philosophers> ", STDERR_FILENO);
	ft_putstr_fd("<time to die> ", STDERR_FILENO);
	ft_putstr_fd("<time to eat> ", STDERR_FILENO);
	ft_putstr_fd("<time to sleep> ", STDERR_FILENO);
	ft_putstr_fd("<[number of times each philosopher ", STDERR_FILENO);
	ft_putstr_fd("must eat]>\n", STDERR_FILENO);
	return (0);
}

int	validate_args(int argc, char **argv)
{
	if (argc != 6)
		return (invalid_arguments(argv[0]));
	return (42);
}
