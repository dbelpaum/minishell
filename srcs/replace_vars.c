/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_vars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbelpaum <dbelpaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 19:52:01 by dbelpaum          #+#    #+#             */
/*   Updated: 2022/06/24 00:54:12 by dbelpaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*ft_strreplace(char *str, char *old, char *new, int start)
{
	char	*ret;
	char	*char_at;
	int		i;

	if (!str)
		return (NULL);
	char_at = ft_strnstr(str + start, old, ft_strlen(str));
	if (!old || !char_at)
		return (str);
	ret = (char *)malloc(sizeof(char)
			* (ft_strlen(str) + ft_strlen(new) - ft_strlen(old) + 1));
	if (!ret)
		return (NULL);
	i = -1;
	while (str + ++i != char_at)
		ret[i] = str[i];
	ret[i] = 0;
	ft_strcat(ret, new);
	i = ft_strlen(ret);
	char_at += ft_strlen(old);
	while (*char_at)
		ret[i++] = *char_at++;
	ret[i] = 0;
	free(str);
	return (ret);
}

static int	find_closest_var(char *str, int start_idx)
{
	int	in_quotes;

	in_quotes = 0;
	if (!str || start_idx >= (int)ft_strlen(str) || start_idx < 0)
		return (-1);
	while (str[start_idx])
	{
		if (str[start_idx] == '\'')
			in_quotes = !in_quotes;
		if (in_quotes == 0 && str[start_idx] && str[start_idx] == '$'
			&& ft_strchr("?$\'\" ", str[start_idx + 1]) == NULL)
			return (start_idx);
		start_idx++;
	}
	return (-1);
}

static char	*parse_var_name(char *str, int start_idx)
{
	char	var_name[256];
	int		i;

	if (!str || start_idx >= (int)ft_strlen(str) || start_idx < 0)
		return (NULL);
	i = 0;
	while (str[start_idx] && str[start_idx] != ' ' && str[start_idx] != '\''
		&& str[start_idx] != '\"')
	{
		var_name[i] = str[start_idx];
		i++;
		start_idx++;
		if (str[start_idx] == '$')
			break ;
	}
	var_name[i] = 0;
	return (ft_strdup(var_name));
}

static char	*replace_q_mark(char *str)
{
	int		i;
	int		in_quotes;
	char	*ret;
	char	*exit_code;

	ret = ft_strdup(str);
	if (!ret)
		return (NULL);
	in_quotes = 0;
	i = -1;
	while (ret[++i])
	{
		if (ret[i] == '\'')
			in_quotes = !in_quotes;
		if (in_quotes == 0 && ret[i] && ret[i] == '$' && ret[i + 1] == '?')
		{
			exit_code = ft_itoa(g_exit_code);
			ret = ft_strreplace(ret, "$?", exit_code, i);
			free(exit_code);
		}
	}
	free(str);
	return (ret);
}

char	*replace_vars(char *str, t_data *data)
{
	char	*ret;
	char	*var_name;
	char	*var_name_raw;
	int		idx;

	ret = ft_strdup(str);
	if (!ret)
		return (NULL);
	idx = find_closest_var(ret, 0);
	while (idx != -1)
	{
		var_name = parse_var_name(ret, idx);
		var_name_raw = ft_substr(var_name, 1, ft_strlen(var_name));
		if (get_env_var(data->envi, var_name_raw))
			ret = ft_strreplace(ret, var_name,
					get_env_var(data->envi, var_name_raw), 0);
		else
			ret = ft_strreplace(ret, var_name, "", 0);
		free(var_name);
		free(var_name_raw);
		idx = find_closest_var(ret, 0);
	}
	ret = replace_q_mark(ret);
	return (ret);
}
