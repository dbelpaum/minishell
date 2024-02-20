/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_vars2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbelpaum <dbelpaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 00:54:06 by dbelpaum          #+#    #+#             */
/*   Updated: 2022/06/24 00:54:48 by dbelpaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*trim_nl(char *str)
{
	char	*ret;
	int		i;

	ret = malloc(sizeof(char) * ft_strlen(str));
	if (!ret)
		return (NULL);
	i = -1;
	while (++i < (int)ft_strlen(str) - 1)
		ret[i] = str[i];
	ret[i] = 0;
	free(str);
	return (ret);
}

char	*replace_vars2(char *str, t_data *my_data)
{
	static t_data	*data = NULL;
	char			*tmp;

	if (data == NULL && !str)
		return (data = my_data, NULL);
	str = trim_nl(str);
	tmp = replace_vars(str, data);
	free(str);
	str = NULL;
	tmp = ft_strjoin_gnl(tmp, "\n");
	return (tmp);
	return (NULL);
}
