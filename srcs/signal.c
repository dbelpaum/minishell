/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbelpaum <dbelpaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:08:53 by dbelpaum          #+#    #+#             */
/*   Updated: 2022/07/28 10:02:03 by dbelpaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	null_handler(int sigid)
{
	if (sigid == SIGINT)
		g_exit_code = 130;
}

void	sig_handler(int sigid)
{
	if (sigid == SIGINT)
	{
		rl_replace_line("", 0);
		write(1, "\n", 1);
		print_prompt(NULL);
		g_exit_code = 130;
	}
	if (sigid == SIGQUIT)
	{
		write(2, "Quit\n", 5);
		g_exit_code = 131;
	}
}
