/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbelpaum <dbelpaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 15:17:45 by ayblin            #+#    #+#             */
/*   Updated: 2022/06/24 00:27:07 by dbelpaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_exit_code = 0;

void	free_data(t_data *data)
{
	int	i;

	i = 0;
	while (data->envi[i])
	{
		free(data->envi[i]);
		i++;
	}
	free(data->envi);
}

static char	**init_null_env(void)
{
	char	**ret;
	char	*pwd;

	ret = malloc(sizeof(char *) * 3);
	if (!ret)
		return (NULL);
	pwd = getcwd(NULL, 0);
	ret[0] = malloc(sizeof(char) * (ft_strlen(pwd) + 5));
	if (!ret[0])
		return (free(ret), NULL);
	ret[0][0] = 0;
	ft_strcat(ret[0], "PWD=");
	ft_strcat(ret[0], pwd);
	ret[1] = malloc(sizeof(char) * (ft_strlen(pwd) + 8));
	if (!ret[1])
		return (free(ret[0]), free(ret), NULL);
	ret[1][0] = 0;
	ft_strcat(ret[1], "OLDPWD=");
	ft_strcat(ret[1], pwd);
	ret[2] = NULL;
	free(pwd);
	return (ret);
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	if (env && *env)
	{
		data.envi = ft_strstrdup(env);
		if (!data.envi)
			return (1);
		data.empty_env = 0;
	}
	else
	{
		data.envi = init_null_env();
		if (!data.envi)
			return (1);
		data.empty_env = 1;
	}
	replace_vars2(NULL, &data);
	print_prompt(&data);
	prompt(&data);
	free_data(&data);
	(void)ac, (void)av, (void)env;
	return (g_exit_code);
}
