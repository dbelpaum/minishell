/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbelpaum <dbelpaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 15:11:04 by dbelpaum          #+#    #+#             */
/*   Updated: 2022/07/26 14:29:24 by dbelpaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	my_exec(t_data *data, t_pipex p, t_redi **t)
{
	(void)t;
	if (ft_strncmp(p.mycmdargs[0], "echo", 5) == 0)
		return (ft_echo(p.mycmdargs, data));
	if (ft_strncmp(p.mycmdargs[0], "cd", 3) == 0)
		return (ft_cd(p.mycmdargs, data));
	if (ft_strncmp(p.mycmdargs[0], "pwd", 4) == 0)
		return (ft_pwd(p.mycmdargs, data));
	if (ft_strncmp(p.mycmdargs[0], "export", 7) == 0)
		return (ft_export(p.mycmdargs, data));
	if (ft_strncmp(p.mycmdargs[0], "unset", 6) == 0)
		return (ft_unset(p.mycmdargs, data));
	if (ft_strncmp(p.mycmdargs[0], "env", 4) == 0)
		return (ft_env(p.mycmdargs, data));
	if (ft_strncmp(p.mycmdargs[0], "exit", 5) == 0)
	{
		rl_clear_history();
		get_next_line(0, 1);
		ft_exit(p.mycmdargs, data, p, t);
	}
	return (0);
}
