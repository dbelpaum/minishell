/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbelpaum <dbelpaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 15:17:46 by dbelpaum          #+#    #+#             */
/*   Updated: 2022/07/26 15:21:03 by dbelpaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_unset(char **args, t_data *data)
{
	int		i;

	i = 0;
	while (args[++i])
	{
		if (ft_isdigit(args[i][0]))
		{
			write(2, "unset: `", 8);
			write(2, args[i], ft_strlen(args[i]));
			write(2, "': not a valid identifier\n", 26);
		}
		if (!*args[i] || find_var(data->envi, args[i]) == -1)
			continue ;
		del_env_var(&data->envi, args[i]);
	}
	return (0);
}
