/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbelpaum <dbelpaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 10:26:57 by dbelpaum          #+#    #+#             */
/*   Updated: 2022/06/22 12:56:24 by dbelpaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	find_var(char **env, char *name)
{
	int	i;

	i = -1;
	if (!env || !*env)
		return (-1);
	while (env[++i])
	{
		if (ft_strncmp(env[i], name, ft_strlen(name)) == 0
			&& env[i][ft_strlen(name)] == '=')
			return (i);
	}
	return (-1);
}

void	update_env_var(char ***old_env, char *name, char *value)
{
	int	idx;

	idx = find_var(old_env[0], name);
	free(old_env[0][idx]);
	old_env[0][idx] = (char *)malloc(sizeof(char)
			* (ft_strlen(name) + ft_strlen(value) + 2));
	if (!old_env[0][idx])
		return ;
	old_env[0][idx][0] = 0;
	ft_strcat(old_env[0][idx], name);
	ft_strcat(old_env[0][idx], "=");
	ft_strcat(old_env[0][idx], value);
}

char	*get_env_var(char **env, char *name)
{
	char	*value;

	if (find_var(env, name) == -1)
		return (NULL);
	value = env[find_var(env, name)];
	value = value + ft_strlen(name) + 1;
	return (value);
}

void	del_env_var(char ***old_env, char *name)
{
	char	**new_env;
	int		i;
	int		j;

	if (find_var(*old_env, name) == -1)
		return ;
	if (!*old_env || !old_env[0][0])
		return ;
	new_env = (char **)malloc(sizeof(char *) * (ft_strstrlen(*old_env)));
	if (!new_env)
		return ;
	i = -1;
	j = -1;
	while (old_env[0][++i])
	{
		if (ft_strncmp(old_env[0][i], name, ft_strlen(name)) != 0
			|| old_env[0][i][ft_strlen(name)] != '=')
			new_env[++j] = ft_strdup(old_env[0][i]);
	}
	new_env[++j] = NULL;
	ft_freestrstr(old_env[0]);
	old_env[0] = new_env;
}

void	add_env_var(char ***old_env, char *name, char *value)
{
	char	**new_env;
	int		i;

	if (!old_env[0] || !*old_env[0])
		old_env[0] = (char **)malloc(sizeof(char *) * 2);
	if (find_var(old_env[0], name) >= 0)
		return (update_env_var(old_env, name, value));
	new_env = (char **)malloc(sizeof(char *) * (ft_strstrlen(old_env[0]) + 2));
	if (!new_env)
		return ;
	i = -1;
	while (old_env[0][++i])
		new_env[i] = ft_strdup(old_env[0][i]);
	new_env[i] = (char *)malloc(sizeof(char)
			* (ft_strlen(name) + ft_strlen(value) + 2));
	if (!new_env[i])
		return ;
	new_env[i][0] = 0;
	ft_strcat(new_env[i], name);
	ft_strcat(new_env[i], "=");
	ft_strcat(new_env[i], value);
	new_env[++i] = NULL;
	ft_freestrstr(old_env[0]);
	old_env[0] = new_env;
}
