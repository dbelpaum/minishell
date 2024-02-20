/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab_new.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayblin <ayblin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 17:23:34 by ayblin            #+#    #+#             */
/*   Updated: 2022/05/03 20:51:22 by ayblin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_tab	*ft_tab_new(char *content)
{
	t_tab	*new;

	new = (t_tab *)malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->str = content;
	new->next = NULL;
	return (new);
}
