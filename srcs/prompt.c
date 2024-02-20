/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbelpaum <dbelpaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 16:58:50 by dbelpaum          #+#    #+#             */
/*   Updated: 2022/07/28 09:59:48 by dbelpaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	add_chars(char *prompt, char *str, int *idx)
{
	int	i;

	if (!str)
		return ;
	i = -1;
	while (str[++i])
	{
		prompt[*idx] = str[i];
		(*idx)++;
	}
	prompt[*idx] = 0;
}

static void	get_prompt(char prompt[2048], t_data *data)
{
	int		idx;
	char	*pwd;
	char	*tmp;

	idx = 0;
	prompt[0] = 0;
	add_chars(prompt, GRN, &idx);
	add_chars(prompt, "Mini@shell:", &idx);
	add_chars(prompt, MAG, &idx);
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (add_chars(prompt, NRM, &idx));
	tmp = pwd;
	if (!data->empty_env && get_env_var(data->envi, "HOME")
		&& ft_strnstr(pwd, get_env_var(data->envi, "HOME"), ft_strlen(pwd)))
	{
		pwd = ft_substr(pwd, ft_strlen(get_env_var(data->envi, "HOME")),
				ft_strlen(pwd));
		free(tmp);
		add_chars(prompt, "~", &idx);
	}
	add_chars(prompt, pwd, &idx);
	add_chars(prompt, "$ ", &idx);
	add_chars(prompt, NRM, &idx);
	free(pwd);
}

void	print_prompt(t_data *data)
{
	char			prompt[2048];
	static t_data	*prev_data = NULL;

	if (data != NULL)
		prev_data = data;
	else
	{
		get_prompt(prompt, prev_data);
		write(1, prompt, ft_strlen(prompt));
	}
}

void	prompt(t_data *data)
{
	char	*str;
	char	prompt[2048];

	while (1)
	{
		get_prompt(prompt, data);
		signal(SIGINT, sig_handler);
		signal(SIGTSTP, sig_handler);
		signal(SIGQUIT, SIG_IGN);
		str = readline(prompt);
		if (!str)
		{
			printf("\nGoodbye");
			get_next_line(0, 1);
			rl_clear_history();
			free_data(data);
			exit(g_exit_code);
		}
		add_history(str);
		signal(SIGINT, null_handler);
		signal(SIGTSTP, null_handler);
		signal(SIGQUIT, sig_handler);
		parsing(str, data, 0);
		free(str);
	}
}
