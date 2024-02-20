/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbelpaum <dbelpaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 14:22:29 by ayblin            #+#    #+#             */
/*   Updated: 2022/06/10 16:21:06 by dbelpaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	child_free2(t_pipex *p, t_redi **t, t_data *data)
{
	free_cmd_tab(t);
	free_data(data);
	free_tab(p->mycmdargs);
	free_tab(data->bloc_cmd);
}

void	child_free(t_pipex *p, t_redi **t, t_data *data)
{
	free_cmd_tab(t);
	free_data(data);
	parent_free(p);
	free_tab(p->mycmdargs);
	free_tab(data->bloc_cmd);
}

void	parent_free(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (pipex->mypaths && pipex->mypaths[i])
	{
		free(pipex->mypaths[i]);
		i++;
	}
	free(pipex->mypaths);
}
