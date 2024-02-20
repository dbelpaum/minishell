/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbelpaum <dbelpaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 14:29:06 by dbelpaum          #+#    #+#             */
/*   Updated: 2022/07/26 14:31:52 by dbelpaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	ft_exit_2(t_data *data, t_pipex p, t_redi **t, int i)
{
	child_free(&p, t, data);
	exit(i);
}

void	ft_exit(char **args, t_data *data, t_pipex p, t_redi **t)
{
	int	has_value;
	int	i;

	has_value = 1;
	i = -1;
	if (ft_strstrlen(args) > 1)
	{
		while (args[1][++i])
		{
			if (!ft_isdigit(args[1][i]))
			{
				write(2, "exit : numeric argument required\n", 33);
				has_value = 0;
				break ;
			}
		}
	}
	else
		has_value = 0;
	if (has_value && ft_strstrlen(args) >= 3)
		return (write(2, "exit : too many arguments\n", 26), (void)0);
	if (has_value)
		ft_exit_2(data, p, t, ft_atoi(args[1]));
	else
		ft_exit_2(data, p, t, g_exit_code);
}
