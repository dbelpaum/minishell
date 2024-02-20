/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbelpaum <dbelpaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 16:10:06 by ayblin            #+#    #+#             */
/*   Updated: 2022/07/28 10:47:06 by dbelpaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	ft_strlen2(const char *s)
{
	unsigned int	len;

	len = -1;
	while (s[++len])
		;
	return (len);
}

int	ft_msg(char *str)
{
	write(2, str, ft_strlen2(str));
	write(2, "\n", 1);
	return (1);
}

void	init_pipex(t_pipex *pipex, int argc)
{
	pipex->save_in = dup(STDIN_FILENO);
	pipex->save_out = dup(STDOUT_FILENO);
	pipex->idx = -1;
	pipex->cmd_nbs = argc ;
	pipex->pipe_nbs = (pipex->cmd_nbs - 1) * 2;
	pipex->fdin = 0;
	pipex->fdout = 1;
}

static void	pipex_norm(int exit_code)
{
	if (exit_code == 131)
		g_exit_code = exit_code;
	else
		g_exit_code = 130;
}

int	pipex(int argc, t_redi **t, t_data *data)
{
	t_pipex	pipex;
	int		exit_code;

	exit_code = g_exit_code;
	init_pipex(&pipex, argc);
	pipex.path_from_envp = get_env_var(data->envi, "PATH");
	if (pipex.path_from_envp)
		pipex.mypaths = ft_split(pipex.path_from_envp, ':');
	else
		pipex.mypaths = NULL;
	while (++(pipex.idx) < pipex.cmd_nbs)
	{
		child(&pipex, t, data);
	}
	while (waitpid(-1, &exit_code, 0) != -1)
	{
		if (g_exit_code != 131)
			g_exit_code = WEXITSTATUS(exit_code);
		if (WIFSIGNALED(exit_code))
			pipex_norm(exit_code);
	}
	dup2(pipex.save_out, STDOUT_FILENO);
	dup2(pipex.save_in, STDIN_FILENO);
	parent_free(&pipex);
	return (0);
}
