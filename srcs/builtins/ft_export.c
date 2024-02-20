/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbelpaum <dbelpaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 15:17:42 by dbelpaum          #+#    #+#             */
/*   Updated: 2022/07/28 09:52:46 by dbelpaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	is_valid_input(char *str)
{
	char	*tmp;
	int		i;

	if (ft_isdigit(str[0]))
		return (0);
	if (!ft_strchr(str, '='))
		return (0);
	if (ft_strchr(str, '=') == str)
		return (0);
	tmp = ft_substr(str, 0, ft_strchr(str, '=') - str);
	if (!tmp)
		return (0);
	i = -1;
	while (tmp[++i])
		if (!ft_isalnum(tmp[i]))
			return (0);
	free(tmp);
	return (1);
}

static void	alphab_sort(char **tab)
{
	char	*tmp;
	int		i;
	int		j;

	i = -1;
	while (tab[++i])
	{
		j = -1;
		while (tab[++j + 1])
		{
			if (ft_strncmp(tab[j], tab[j + 1], 2147483647) > 0)
			{
				tmp = tab[j];
				tab[j] = tab[j + 1];
				tab[j + 1] = tmp;
			}
		}
	}
}

static int	export_raw(char **env)
{
	int		i;

	alphab_sort(env);
	i = -1;
	while (env[++i])
	{
		ft_putstr_fd("export ", 1);
		ft_putstr_fd(env[i], 1);
		ft_putstr_fd("\n", 1);
	}
	free_tab(env);
	return (0);
}

int	ft_export(char **args, t_data *data)
{
	int		i;
	char	*tmp;

	i = 0;
	if (ft_strstrlen(args) == 1)
		return (export_raw(ft_strstrdup(data->envi)));
	while (args[++i])
	{
		if (!is_valid_input(args[i]))
		{
			ft_putstr_fd("minishell: export: ", 2);
			ft_putstr_fd(args[i], 2);
			ft_putendl_fd(": invalid argument", 2);
			continue ;
		}
		tmp = ft_substr(args[i], 0, ft_strchr(args[i], '=') - args[i]);
		if (!tmp)
			return (0);
		if (find_var(data->envi, tmp) == -1)
			add_env_var(&data->envi, tmp, args[i] + ft_strlen(tmp) + 1);
		else
			update_env_var(&data->envi, tmp, args[i] + ft_strlen(tmp) + 1);
		free(tmp);
	}
	return (0);
}
