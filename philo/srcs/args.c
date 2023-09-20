/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 11:42:56 by maalexan          #+#    #+#             */
/*   Updated: 2023/09/19 22:30:28 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static t_bool	invalid_arguments(char *program_name)
{
	ft_putstr_fd("Usage: ", STDERR_FILENO);
	ft_putstr_fd(program_name, STDERR_FILENO);
	ft_putstr_fd(STR_USAGE, STDERR_FILENO);
	return (FALSE);
}

t_bool	validate_args(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (invalid_arguments(argv[0]));
	return (TRUE);
}
