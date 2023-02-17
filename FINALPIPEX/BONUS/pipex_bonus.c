/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicoule <tpicoule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 07:59:38 by tpicoule          #+#    #+#             */
/*   Updated: 2023/02/17 14:29:25 by tpicoule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_openfile(t_pipex *value, char **argv, int argc)
{
	value->file1 = open(argv[1], O_RDONLY, 0777);
	value->file2 = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (value->file1 == -1 || value->file2 == -1)
		return (write (1, "file problem\n", 13), 1);
	return (0);
}

void	ft_freepathargu(t_pipex *value)
{
	int		i;

	i = 0;
	free(value->path);
	while (value->argu[i])
		free(value->argu[i++]);
	free(value->argu);
	free(value);
	write (1, "Error path\n", 11);
	exit(1);
}

void	ft_lastcmd(char **env, int *pipefd, t_pipex *value)
{
	int		pid;
	int		i;

	i = 0;
	pipe(pipefd);
	pid = fork();
	if (pid == 0)
	{
		dup2(value->file2, STDOUT_FILENO);
		close(pipefd[1]);
		close(pipefd[0]);
		execve(value->path, value->argu, env);
	}
	waitpid(pid, NULL, 0);
	free(value->path);
	while (value->argu[i])
		free(value->argu[i++]);
	free(value->argu);
	close(pipefd[1]);
	close(pipefd[0]);
}

void	ft_cmd(char **env, t_pipex *value, int *pipefd)
{
	int		pid;
	int		i;

	i = 0;
	pipe(pipefd);
	pid = fork();
	if (pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		execve(value->path, value->argu, env);
	}
	waitpid(pid, NULL, 0);
	free(value->path);
	while (value->argu[i])
		free(value->argu[i++]);
	free(value->argu);
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
}

int	main(int argc, char **argv, char **env)
{
	int		pipefd[2];
	t_pipex	*value;

	if (argc < 4)
		return (write(1, "argc error\n", 11), 1);
	value = malloc(sizeof(*value));
	value->i = 2;
	if (ft_openfile(value, argv, argc) == 1)
		return (free (value), 0);
	dup2(value->file1, STDIN_FILENO);
	while (value->i < argc - 2)
	{
		value->argu = funct_split(argv[value->i++], ' ');
		value->path = ft_find_path(env, value->argu[0], value);
		if (!value->path)
			ft_freepathargu(value);
		ft_cmd(env, value, pipefd);
	}
	value->argu = funct_split(argv[value->i], ' ');
	value->path = ft_find_path(env, value->argu[0], value);
	if (!value->path)
		ft_freepathargu(value);
	ft_lastcmd(env, pipefd, value);
	return (free(value), 0);
}
