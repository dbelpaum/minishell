/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbelpaum <dbelpaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 22:58:57 by ayblin            #+#    #+#             */
/*   Updated: 2022/06/24 12:15:26 by dbelpaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_redi(t_redi *redi)
{
	printf("\x1B[37m|||CELL|||\n \x1B[0m ");
	printf("\x1B[37mcmd line :%s\n \x1B[0m ", redi->cmd);
	printf("\x1B[37mfdoud : %d\n \x1B[0m ", redi->fd_out);
	printf("\x1B[37mfdin : %d\n \x1B[0m ", redi->fd_in);
	printf("\x1B[37midin : %d\n \x1B[0m ", redi->idin);
	printf("\x1B[37midout : %d\n \x1B[0m ", redi->idout);
	printf("\x1B[37mhere_doc : %s\n \x1B[0m ", redi->here_doc);
	printf("\x1B[37m|||||||||\n \x1B[0m ");
}

void	init_value_redi(t_redi *redi_cell)
{
	redi_cell->cmd = 0;
	redi_cell->fd_out = 0;
	redi_cell->fd_in = 0;
	redi_cell->idin = 0;
	redi_cell->idout = 0;
	redi_cell->here_doc = 0;
}

t_redi	*remove_redi(char *str, int i, t_redi *cell_redi, char c)
{
	cell_redi = malloc(sizeof(t_redi));
	init_value_redi(cell_redi);
	cell_redi->cmd = str;
	while (++i < (int)ft_strlen(str) && str[i])
	{
		if (str[i] == '>' && str[i + 1] && str[i + 1] == '>')
			get_redir1(str + i, cell_redi);
		else if (str[i] == '>' && str[i + 1] != '>')
			get_redir2(str + i, cell_redi);
		if (str[i] == '<' && str[i + 1] && str[i + 1] == '<')
			get_redir4(str + i, cell_redi);
		else if (str[i] == '<' && str[i + 1] != '<')
			get_redir3(str + i, cell_redi);
		if (str[i] == '"' || str[i] == '\'')
		{
			c = str[i++];
			while (str[i] && str[i] != c)
				i++;
			if (str[i] == c)
				i++;
		}
	}
	return (cell_redi);
}

int	get_redir_len(char *str, int i)
{
	int		len;
	char	c;

	len = 0;
	while (str[i] == ' ')
		i++;
	while (str[i + len])
	{
		if (str[i + len] == ' ')
			break ;
		else if (str[i + len] == '"' || str[i + len] == '\'')
		{
			c = str[i + len];
			i++;
			while (str[i + len] && str[i + len] != c)
				len++;
			i++;
		}
		if (str[i + len] && str[i + len] != ' ')
			len++;
	}
	return (len);
}

void	get_fd(char *str, char *redi, int i, int len)
{
	char	c;
	int		j;

	j = 0;
	while (j < len)
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			c = str[i];
			str[i] = ' ';
			i++;
			while (str[i] != c)
			{
				redi[j++] = str[i];
				str[i++] = ' ';
			}
			str[i++] = ' ';
		}
		if (j < len)
		{
			redi[j++] = str[i];
			str[i++] = ' ';
		}
	}
	redi[j] = 0;
}
