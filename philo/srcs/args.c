/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 11:42:56 by maalexan          #+#    #+#             */
/*   Updated: 2023/09/20 18:10:44 by maalexan         ###   ########.fr       */
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

static t_bool	check_digit_inputs(char **argv)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		while (ft_isdigit(*argv[i]))
			argv[i]++;
		if (*argv[i])
			return (FALSE);
		i++;
	}
	return (TRUE);
}

t_bool	validate_args(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (invalid_arguments(argv[0]));
	if (!check_digit_inputs(argv + 1))
		return (invalid_arguments(argv[0]));
	return (TRUE);
}
