/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbelpaum <dbelpaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 15:17:38 by dbelpaum          #+#    #+#             */
/*   Updated: 2022/06/10 16:10:21 by dbelpaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	normedemerde(char *oldpwd, char *tmppwd)
{
	free(oldpwd);
	free(tmppwd);
	return (0);
}

static void	cestcoollanorme(char **oldpwd, t_data *data, char *tmppwd)
{
	*oldpwd = ft_strdup(get_env_var(data->envi, "PWD"));
	update_env_var(&data->envi, "PWD", tmppwd);
}

int	ft_cd(char **args, t_data *data)
{
	char	*oldpwd;
	char	*tmppwd;

	if (ft_strstrlen(args) != 2)
		return (write(2, "cd: invalid arguments\n", 22), 1);
	else if (chdir(args[1]) == 0)
	{
		tmppwd = getcwd(NULL, 0);
		if (get_env_var(data->envi, "PWD"))
			cestcoollanorme(&oldpwd, data, tmppwd);
		else
		{
			oldpwd = ft_strdup(tmppwd);
			add_env_var(&data->envi, "PWD", tmppwd);
		}
		if (get_env_var(data->envi, "OLDPWD"))
			update_env_var(&data->envi, "OLDPWD", oldpwd);
		else
			add_env_var(&data->envi, "OLDPWD", oldpwd);
		return (normedemerde(oldpwd, tmppwd));
	}
	else
		return (write(2, "cd : can't access this directory\n", 33), 1);
	return (0);
}
