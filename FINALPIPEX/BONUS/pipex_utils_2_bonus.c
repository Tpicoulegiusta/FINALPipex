/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_2_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicoule <tpicoule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 11:26:55 by tpicoule          #+#    #+#             */
/*   Updated: 2023/02/17 14:04:42 by tpicoule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

	i = -1;
	while (env[++i])
	{
		if (env[i][0] == 'P' && env[i][1] == 'A' && env[i][2] == 'T'
		&& env[i][3] == 'H')
			break ;
	}
	value->newenv = ft_substr(env[i], 5, ft_strlen(env[i]));
	value->goodpath = funct_split(value->newenv, ':');
	free (value->newenv);
	i = 0;
	while (value->goodpath[i])
	{
		value->newenv = ft_strjoin(value->goodpath[i++], cmd);
		if (access(value->newenv, F_OK) == 0)
		{
			ft_freegoodpath(value);
			return (value->newenv);
		}
		free (value->newenv);
	}
	ft_freegoodpath(value);
	return (NULL);
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
