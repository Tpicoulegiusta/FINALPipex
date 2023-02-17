/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicoule <tpicoule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 11:26:55 by tpicoule          #+#    #+#             */
/*   Updated: 2023/02/17 14:06:28 by tpicoule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_freegoodpath(t_pipex *value)
{
	int		i;

	i = 0;
	if (value->goodpath)
	{
		while (value->goodpath[i])
			free(value->goodpath[i++]);
		free(value->goodpath);
	}
}

char	*ft_find_path(char **env, char *cmd, t_pipex *value)
{
	int		i;
	int		test;

	i = -1;
	while (env[++i])
	{
		if (env[i][0] == 'P' && env[i][1] == 'A' && env[i][2] == 'T'
		&& env[i][3] == 'H')
			break ;
	}
	value->newenv = ft_substr(env[i], 5, ft_strlen(env[i]));
	value->goodpath = funct_split(value->newenv, ':');
	i = -1;
	test = 42;
	while (test != 0 && value->goodpath[++i])
	{
		if (test != 0)
			free(value->newenv);
		value->newenv = ft_strjoin(value->goodpath[i], cmd);
		test = access(value->newenv, F_OK);
	}
	i = 0;
	ft_freegoodpath(value);
	if (test == -1)
		return (write(1, "Error path\n", 11), free(value->newenv), NULL);
	return (value->newenv);
}

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoinfree(char *stock, char *tmp)
{
	char	*str;

	str = ft_strjoin(stock, tmp);
	if (stock)
		free (stock);
	return (str);
}
