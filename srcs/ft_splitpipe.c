/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitpipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayblin <ayblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 18:55:01 by ayblin            #+#    #+#             */
/*   Updated: 2022/06/23 02:44:49 by ayblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	ft_countwordspipe(const char *str, char c)
{
	int		i;
	int		n;
	char	tmp;

	i = 0;
	n = 0;
	while (str[i] && str[i] == c)
		i++;
	while (str[i])
	{
		n++;
		while (str[i] && str[i] != c)
		{
			if (str[i] == '"' || str[i] == '\'')
			{
				tmp = str[i++];
				while (str[i] && str[i] != tmp)
					i++;
			}
			i++;
		}
		while (str[i] == c)
			i++;
	}
	return (n);
}

static int	count_lenpipe(const char *str, char c)
{
	int		i;
	char	tmp;

	i = 0;
	while (str[i])
	{
		while (str[i] && str[i] != '\'' && str[i] != '"' && str[i] != c)
			i++;
		if (str[i] == '"' || str[i] == '\'')
		{
			tmp = str[i];
			i++;
			while (str[i] && str[i] != tmp)
				i++;
			i++;
		}
		if (str[i] == c)
			break ;
	}
	return (i);
}

static char	*ft_get_wordspipe(const char *str, char c, char **tab, int i)
{
	char	*ret;
	int		len;

	len = count_lenpipe(str, c);
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (free_tab(tab));
	while (i < len)
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

char	**ft_splitpipenorm(char *s, char c, int i, int n)
{
	char	**tab;
	char	tmp;

	tab = malloc(sizeof(const char *) * (n + 1));
	tab[n] = 0;
	while (*s == c)
		s++;
	while (*s)
	{
		tab[i++] = ft_get_wordspipe((const char *)s, c, tab, 0);
		while (*s && *s != c)
		{
			if (*s == '"' || *s == '\'')
			{
				tmp = *s;
				s++;
				while (*s && *s != tmp)
					s++;
			}
			s++;
		}
		while (*s == c)
			s++;
	}
	return (tab);
}

char	**ft_splitpipe(char *s, char c)
{
	int	n;

	n = ft_countwordspipe(s, c);
	return (ft_splitpipenorm(s, c, 0, n));
}
