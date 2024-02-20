/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayblin <ayblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 00:26:12 by ayblin            #+#    #+#             */
/*   Updated: 2022/06/22 23:37:15 by ayblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	get_redir1(char *str, t_redi *cell_redi)
{
	int			i;
	int			len;
	char		*redi_out;

	i = 2;
	cell_redi->idout = 1;
	while (str[i] == ' ')
		i++;
	len = get_redir_len(str, i);
	redi_out = malloc(sizeof(char) * (len + 1));
	while (str[i] == ' ')
		i++;
	get_fd(str, redi_out, i, len);
	cell_redi->fd_out = open(redi_out, O_CREAT | O_WRONLY | O_APPEND, 0000644);
	free(redi_out);
	if (!cell_redi->fd_out)
		exit(0);
	str[0] = ' ';
	str[1] = ' ';
}

void	get_redir2(char *str, t_redi *cell_redi)
{
	int			i;
	int			len;
	char		*redi_out;

	i = 1;
	cell_redi->idout = 1;
	while (str[i] == ' ')
		i++;
	len = get_redir_len(str, i);
	redi_out = malloc(sizeof(char) * (len + 1));
	while (str[i] == ' ')
		i++;
	get_fd(str, redi_out, i, len);
	cell_redi->fd_out = open(redi_out, O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	free(redi_out);
	if (!cell_redi->fd_out)
		exit(0);
	str[0] = ' ';
}

void	get_redir3(char *str, t_redi *cell_redi)
{
	int			i;
	int			len;
	char		*redi_out;

	i = 1;
	cell_redi->idin = 1;
	while (str[i] == ' ')
		i++;
	len = get_redir_len(str, i);
	redi_out = malloc(sizeof(char) * (len + 1));
	while (str[i] == ' ')
		i++;
	get_fd(str, redi_out, i, len);
	cell_redi->fd_in = open(redi_out, O_RDONLY);
	free(redi_out);
	if (!cell_redi->fd_in)
		exit(0);
	str[0] = ' ';
}

void	get_redir4(char *str, t_redi *cell_redi)
{
	int			i;
	int			len;
	char		*redi_out;

	i = 2;
	cell_redi->idin = 2;
	while (str[i] == ' ')
		i++;
	len = get_redir_len(str, i);
	redi_out = malloc(sizeof(char) * (len + 1));
	while (str[i] == ' ')
		i++;
	get_fd(str, redi_out, i, len);
	cell_redi->fd_in = here_doc(redi_out);
	free(redi_out);
	str[0] = ' ';
	str[1] = ' ';
}
