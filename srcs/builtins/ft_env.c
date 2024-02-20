/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayblin <ayblin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 15:17:26 by dbelpaum          #+#    #+#             */
/*   Updated: 2022/05/16 21:52:30 by ayblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_env(char **args, t_data *data)
{
	int	i;

	(void)args;
	i = -1;
	while (data->envi[++i])
	{
		ft_putstr_fd(data->envi[i], 1);
		ft_putstr_fd("\n", 1);
	}
	return (0);
}
