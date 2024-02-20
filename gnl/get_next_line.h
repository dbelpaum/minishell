/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbelpaum <dbelpaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 09:23:38 by dbelpaum          #+#    #+#             */
/*   Updated: 2021/12/08 23:50:33 by dbelpaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>

size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);
char	*ft_substr_gnl(char *s, unsigned int start, size_t len, int freeflag);
char	*ft_strjoin_gnl(char *s1, char const *s2);
char	*ft_strchr(const char *s, int c);
char	*get_next_line(int fd, int param);
char	*read_line(int fd, char **fd_save, char *read_buffer);
char	*read_runtime(int fd, char *res, char	*read_buffer);
void	*check_newline(char **res, char **fd_save);
void	free_ptr(char **ptr);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif
# ifndef FD_LIMIT
#  define FD_LIMIT 256
# endif
#endif