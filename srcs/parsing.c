/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayblin <ayblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 17:08:37 by ayblin            #+#    #+#             */
/*   Updated: 2022/06/23 22:21:16 by ayblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	tab_len(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int	check_syntax(t_redi **r)
{
	int	i;

	i = 0;
	while (r[i])
	{
		if (r[i]->fd_in == -1)
		{
			ft_putstr_fd("No such file or directory\n", 2);
			return (0);
		}
		if (r[i]->fd_out == -1)
		{
			ft_putstr_fd("Error : syntax\n", 2);
			return (0);
		}
		i++;
	}
	return (1);
}

static int	exit_error_syntax(t_redi **cmd_tab, t_data *data)
{
	free_cmd_tab(cmd_tab);
	free_tab(data->bloc_cmd);
	return (0);
}

static void	parsing_norm(t_redi **cmd_tab, t_data *data)
{
	int	n;

	n = tab_len(data->bloc_cmd);
	if (data->empty_env == 0)
		pipex(n, cmd_tab, data);
	else
		pipex2(n, cmd_tab, data);
	free_cmd_tab(cmd_tab);
	free_tab(data->bloc_cmd);
}

int	parsing(char *str, t_data *data, int i)
{
	t_redi	**cmd_tab;

	if (is_empty_str(str))
		return (1);
	else if (uneven_quotes(str))
		ft_putstr_fd("Error : Uneven number of quotes\n", 2);
	else
	{
		str = replace_vars(str, data);
		data->bloc_cmd = ft_splitpipe(str, '|');
		free(str);
		if (!data->bloc_cmd)
			exit(1);
		cmd_tab = malloc(sizeof(t_redi *) * ((tab_len(data->bloc_cmd) + 1)));
		while (data->bloc_cmd[i])
		{
			cmd_tab[i] = remove_redi(data->bloc_cmd[i], -1, 0, 0);
			i++;
		}
		cmd_tab[i] = 0;
		if (!check_syntax(cmd_tab))
			return (exit_error_syntax(cmd_tab, data));
		parsing_norm(cmd_tab, data);
	}
	return (999999);
}
