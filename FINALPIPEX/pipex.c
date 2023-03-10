/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpicoule <tpicoule@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 07:59:38 by tpicoule          #+#    #+#             */
/*   Updated: 2023/02/17 14:07:04 by tpicoule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

	if (argc != 5)
		return (write(1, "argc error\n", 11), 1);
	value = malloc(sizeof(*value));
	if (!value)
		return (0);
	value->i = 2;
	value->file1 = open(argv[1], O_RDONLY, 0777);
	value->file2 = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (value->file1 == -1 || value->file2 == -1)
		return (free(value), write (1, "file problem\n", 13), 1);
	dup2(value->file1, STDIN_FILENO);
	while (value->i < argc - 2)
	{
		value->argu = funct_split(argv[value->i++], ' ');
		value->path = ft_find_path(env, value->argu[0], value);
		if (!value->path)
			return (write (1, "Error path\n", 11), 1);
		ft_cmd(env, value, pipefd);
	}
	value->argu = funct_split(argv[value->i], ' ');
	value->path = ft_find_path(env, value->argu[0], value);
	ft_lastcmd(env, pipefd, value);
	free(value);
	return (EXIT_SUCCESS);
}
