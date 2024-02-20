/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayblin <ayblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 03:39:28 by ayblin            #+#    #+#             */
/*   Updated: 2022/05/24 13:53:30 by ayblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	uneven_quotes(char *str)
{
	int		i;
	int		d;
	char	c;

	i = 0;
	d = 0;
	while (str && i < (int)ft_strlen(str) && str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			c = str[i];
			d = 1;
			i++;
			while (str[i] && str[i] != c)
				i++;
			if (str[i] == c)
				d = 0;
		}
		i++;
	}
	return (d);
}

int	count_len(const char *str)
{
	int		i;
	int		d;
	char	c;

	i = 0;
	d = 0;
	while (str[i])
	{
		while (str[i] && str[i] != '\'' && str[i] != '"' && str[i] != ' ')
			i++;
		if (str[i] == '"' || str[i] == '\'')
		{
			c = str[i];
			d = d + 2;
			i++;
			while (str[i] && str[i] != c)
				i++;
			i++;
		}
		if (str[i] == ' ')
			break ;
	}
	return (i - d);
}
