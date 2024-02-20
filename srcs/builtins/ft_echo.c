/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbelpaum <dbelpaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 15:17:36 by dbelpaum          #+#    #+#             */
/*   Updated: 2022/06/22 13:14:20 by dbelpaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	is_option(char *str)
{
	int	i;

	if (!str || ft_strlen(str) < 2 || str[0] != '-')
		return (0);
	i = 0;
	while (str[++i])
	{
		if (str[i] != 'n')
			return (0);
	}
	return (1);
}

static int	check_option(char **args)
{
	int	i;

	i = 0;
	while (args[++i] && is_option(args[i]))
		;
	return (i - 1);
}

int	ft_echo(char **args, t_data *data)
{
	int	has_dash_n;
	int	i;

	has_dash_n = check_option(args);
	i = has_dash_n;
	while (args[++i])
	{
		write(1, args[i], ft_strlen(args[i]));
		if (args[i + 1])
			write(1, " ", 1);
	}
	if (!has_dash_n)
		write(1, "\n", 1);
	(void)data;
	return (0);
}
