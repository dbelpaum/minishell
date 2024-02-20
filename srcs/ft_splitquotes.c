/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitquotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayblin <ayblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 01:27:22 by ayblin            #+#    #+#             */
/*   Updated: 2022/06/08 20:05:20 by ayblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	ft_countwords(const char *str, char c)
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
		while (str[i] && str[i] != ' ')
		{
			if (str[i] == '"' || str[i] == '\'')
			{
				tmp = str[i++];
				while (str[i] && str[i] != tmp)
					i++;
			}
			i++;
		}
		while (str[i] == ' ' )
			i++;
	}
	return (n);
}

char	*free_tab(char **tab)
{
	unsigned int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (0);
}

static char	*ft_get_words2(const char *str, char c, char **tab, int i)
{
	char	*ret;
	int		len;
	int		j;

	j = 0;
	len = count_len(str);
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (free_tab(tab));
	while (i < len)
	{
		while (str[j] != '"' && str[j] != '\'' && i < len)
			ret[i++] = str[j++];
		if (str[j] && (str[j] == '"' || str[j] == '\''))
		{
			c = str[j++];
			while (str[j] && str[j] != c)
				ret[i++] = str[j++];
			j++;
		}
	}
	ret[i] = '\0';
	return (ret);
}

char	**ft_splitquotesnorm(char *s, char c, int i, int n)
{
	char	**tab;
	char	tmp;

	tab = malloc(sizeof(const char *) * (n + 1));
	tab[n] = 0;
	while (*s == ' ')
		s++;
	while (*s)
	{
		tab[i++] = ft_get_words2((const char *)s, c, tab, 0);
		while (*s && *s != ' ')
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
		while (*s == ' ' )
			s++;
	}
	return (tab);
}

char	**ft_splitquotes(char *s, char c)
{
	int	n;

	n = ft_countwords(s, c);
	return (ft_splitquotesnorm(s, c, 0, n));
}
