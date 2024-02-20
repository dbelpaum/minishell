/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbelpaum <dbelpaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 11:34:18 by rigel             #+#    #+#             */
/*   Updated: 2022/06/24 11:50:03 by dbelpaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	exec_child2(t_pipex *p, t_redi **t, t_data *data)
{
	if (is_builtin2(p->mycmdargs[0]))
	{
		g_exit_code = my_exec(data, *p, t);
		child_free2(p, t, data);
		exit (0);
	}
}

int	child2(t_pipex *p, t_redi **t, t_data *data)
{
	pid_t	pid;
	int		pipe_fd[2];

	if (is_empty_str(t[p->idx]->cmd))
		return (0);
	if (pipe(pipe_fd) < 0)
		return (-1);
	p->mycmdargs = ft_splitquotes(t[p->idx]->cmd, ' ');
	if (!is_builtin(p->mycmdargs[0]) && !is_builtin2(p->mycmdargs[0]))
		return (free_tab(p->mycmdargs),
			write(2, "Command not found.\n", 19), 0);
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
		exec_child2(p, t, data);
	return (0);
}
