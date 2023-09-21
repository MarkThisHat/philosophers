/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 11:42:56 by maalexan          #+#    #+#             */
/*   Updated: 2023/09/20 22:48:01 by maalexan         ###   ########.fr       */
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

static t_bool	check_digit_inputs(char *arg)
{
	if (!*arg)
		return (FALSE);
	while (ft_isdigit(*arg))
		arg++;
	if (*arg)
		return (FALSE);
	return (TRUE);
}

static t_bool	check_usability(char **argv)
{
	if (ft_atoui(argv[0]) > MAX_PHIL)
	{
		ft_putstr_fd("Too many philosophers\n", STDERR_FILENO);
		return (FALSE);
	}
	return (TRUE);
}

t_bool	validate_args(int argc, char **argv)
{
	int	i;

	if (argc < 5 || argc > 6)
		return (invalid_arguments(argv[0]));
	i = 0;
	while (++i < 5)
	{
		if (!check_digit_inputs(argv[i]))
			return (invalid_arguments(argv[0]));
	}
	if (!check_usability(argv + 1))
		return (FALSE);
	return (TRUE);
}
