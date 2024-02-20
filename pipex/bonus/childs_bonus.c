/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbelpaum <dbelpaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 16:19:52 by dbelpaum          #+#    #+#             */
/*   Updated: 2022/06/24 11:52:27 by dbelpaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*get_cmd(char *path, char *cmd)
{
	char	*tmp;
	char	*command;

	tmp = ft_strjoin(path, "/");
	command = ft_strjoin(tmp, cmd);
	free(tmp);
	return (command);
}

int	is_cmd(t_pipex p, t_redi **t)
{
	int		i;
	char	*tmp;

	i = -1;
	p.mycmdargs = ft_splitquotes(t[p.idx]->cmd, ' ');
	if (p.mycmdargs[0] && access(p.mycmdargs[0], F_OK + X_OK) == 0)
	{
		free_tab(p.mycmdargs);
		return (1);
	}
	while (p.mypaths && p.mypaths[++i])
	{
		tmp = get_cmd(p.mypaths[i], p.mycmdargs[0]);
		if (tmp && access(tmp, F_OK) == 0)
			return (free(tmp), free_tab(p.mycmdargs), 1);
		free(tmp);
	}
	if (p.mycmdargs[0]
		&& (is_builtin(p.mycmdargs[0]) || is_builtin2(p.mycmdargs[0])))
		return (free_tab(p.mycmdargs), 1);
	free_tab(p.mycmdargs);
	return (0);
}

void	ft_fds(t_pipex p, pid_t pid, int *pipe_fd, t_redi **t)
{
	if (pid == 0)
	{
		if (t[p.idx]->idin == 2)
			dup2(t[p.idx]->fd_in, 0);
		if (t[p.idx]->idin == 1)
			dup2(t[p.idx]->fd_in, 0);
		else if (p.idx == 0)
			dup2(p.fdin, 0);
		if (t[p.idx]->idout > 0)
			dup2(t[p.idx]->fd_out, 1);
		else if (p.idx == (p.cmd_nbs - 1))
			dup2(p.fdout, 1);
		else
			dup2(pipe_fd[1], 1);
		close(pipe_fd[1]);
		close(pipe_fd[0]);
	}
	else
	{
		dup2(pipe_fd[0], 0);
		close(pipe_fd[1]);
		close(pipe_fd[0]);
	}
}

int	child_exec(t_pipex *p, t_redi **t, t_data *data)
{
	int	i;

	i = 0;
	if (is_builtin2(p->mycmdargs[0]))
	{
		g_exit_code = my_exec(data, *p, t);
		child_free(p, t, data);
		exit (0);
	}
	execve(p->mycmdargs[0], p->mycmdargs, data->envi);
	while (p->mypaths[i])
	{
		p->cmd = get_cmd(p->mypaths[i], p->mycmdargs[0]);
		execve(p->cmd, p->mycmdargs, data->envi);
		i++;
	}
	return (0);
}

int	child(t_pipex *p, t_redi **t, t_data *data)
{
	pid_t	pid;
	int		pipe_fd[2];

	if (pipe(pipe_fd) < 0)
		return (-1);
	if (is_empty_str(t[p->idx]->cmd))
		return (0);
	if (!is_cmd(*p, t))
		return (g_exit_code = 127, write(2, "Command not found.\n", 19), 0);
	p->mycmdargs = ft_splitquotes(t[p->idx]->cmd, ' ');
	if (is_builtin(p->mycmdargs[0]))
	{
		g_exit_code = my_exec(data, *p, t);
		free_tab(p->mycmdargs);
		return (0);
	}
	pid = fork();
	if (pid == -1)
		return (-1);
	ft_fds(*p, pid, pipe_fd, t);
	if (pid == 0)
		child_exec(p, t, data);
	free_tab(p->mycmdargs);
	return (0);
}
