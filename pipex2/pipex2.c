/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayblin <ayblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 18:28:58 by ayblin            #+#    #+#             */
/*   Updated: 2022/05/24 11:22:40 by ayblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	pipex2(int argc, t_redi **t, t_data *data)
{
	t_pipex	pipex;
	int		exit_code;

	pipex.save_in = dup(STDIN_FILENO);
	pipex.save_out = dup(STDOUT_FILENO);
	pipex.idx = -1;
	pipex.cmd_nbs = argc ;
	pipex.pipe_nbs = (pipex.cmd_nbs - 1) * 2;
	pipex.fdin = 0;
	pipex.fdout = 1;
	while (++(pipex.idx) < pipex.cmd_nbs)
	{
		child2(&pipex, t, data);
		waitpid(-1, &exit_code, 0);
		exit_code = WEXITSTATUS(exit_code);
		if (exit_code != 127)
			g_exit_code = exit_code;
	}
	dup2(pipex.save_out, STDOUT_FILENO);
	dup2(pipex.save_in, STDIN_FILENO);
	return (0);
}
