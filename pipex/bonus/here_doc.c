/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbelpaum <dbelpaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 12:11:09 by ayblin            #+#    #+#             */
/*   Updated: 2022/06/24 12:09:36 by dbelpaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	here_doc(char *limiter)
{
	int			file;
	char		*buf;

	signal(SIGINT, null_handler);
	signal(SIGTSTP, null_handler);
	file = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	if (file < 0)
		ft_msg("Error here_doc.\n");
	while (1)
	{
		write(1, "heredoc> ", 9);
		buf = get_next_line(0, 0);
		if (!buf)
			return (-1);
		buf = replace_vars2(buf, NULL);
		if (!ft_strncmp(limiter, buf, ft_strlen(limiter))
			&& buf[ft_strlen(limiter)] == '\n')
		{
			free(buf);
			break ;
		}
		write(file, buf, ft_strlen(buf));
		free(buf);
	}
	return (close(file), open(".heredoc_tmp", O_RDONLY));
}
