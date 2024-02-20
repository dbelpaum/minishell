/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbelpaum <dbelpaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 09:23:41 by dbelpaum          #+#    #+#             */
/*   Updated: 2021/12/09 00:30:08 by dbelpaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd, int param)
{
	static char	*fd_saves[FD_LIMIT];
	char		*line;
	char		*read_buffer;

	if (param == 1)
		return (free(fd_saves[fd]), NULL);
	if (fd < 0 || fd >= FD_LIMIT || BUFFER_SIZE < 1)
		return (NULL);
	read_buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!read_buffer)
		return (NULL);
	line = read_line(fd, &fd_saves[fd], read_buffer);
	if (!line)
		return (free(read_buffer), NULL);
	free(read_buffer);
	return (line);
}

char	*read_line(int fd, char **fd_save, char *read_buffer)
{
	char		*res;

	if (fd_save[fd])
	{
		res = ft_strdup(fd_save[fd]);
		free_ptr(&fd_save[fd]);
		fd_save[fd] = ft_strdup("");
		if (!fd_save[fd])
			return (free_ptr(&res), NULL);
	}
	else
		res = ft_strdup("");
	if (!res)
		return (NULL);
	res = read_runtime(fd, res, read_buffer);
	if (!res)
		return (free_ptr(&fd_save[fd]), NULL);
	if (!check_newline(&res, &fd_save[fd]))
		return (NULL);
	return (res);
}

void	*check_newline(char **res, char **fd_save)
{
	char	*nlpos;

	if (ft_strchr(*res, '\n'))
	{
		nlpos = ft_strchr(*res, '\n');
		if (*fd_save)
			free_ptr(fd_save);
		*fd_save = ft_substr_gnl(*res, nlpos - *res + 1,
				ft_strlen(*res) - (nlpos - *res), 0);
		*res = ft_substr_gnl(*res, 0, nlpos - *res + 1, 1);
		if (!(*res) || !(*fd_save))
			return (NULL);
	}
	else if (*fd_save)
		free_ptr(&(*fd_save));
	return ((void *)1);
}

char	*read_runtime(int fd, char *res, char	*read_buffer)
{
	int	chars_read;

	chars_read = BUFFER_SIZE;
	while (!ft_strchr(res, '\n') && chars_read == BUFFER_SIZE)
	{
		chars_read = read(fd, read_buffer, BUFFER_SIZE);
		if (*res && chars_read < 1)
			return (res);
		else if (chars_read < 1)
			return (free(res), NULL);
		read_buffer[chars_read] = 0;
		res = ft_strjoin_gnl(res, read_buffer);
		if (!res)
			return (NULL);
	}
	return (res);
}

void	free_ptr(char **ptr)
{
	if (ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}
