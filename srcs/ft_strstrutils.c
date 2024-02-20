/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstrutils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbelpaum <dbelpaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 12:27:38 by dbelpaum          #+#    #+#             */
/*   Updated: 2022/06/22 12:20:44 by dbelpaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_freestrstr(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}

int	ft_strstrlen(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	**ft_strstrdup(char **env)
{
	char	**new;
	int		i;

	if (!env || !*env)
		return (NULL);
	new = (char **)malloc(sizeof(char *) * (ft_strstrlen(env) + 1));
	if (!new)
		return (NULL);
	i = -1;
	while (env[++i])
	{
		new[i] = ft_strdup(env[i]);
		if (!new[i])
			return (NULL);
	}
	new[i] = NULL;
	return (new);
}

int	is_empty_str(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\r'
			&& str[i] != '\v' && str[i] != '\f')
			return (0);
	return (1);
}
