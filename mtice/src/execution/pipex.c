/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 14:44:07 by mtice             #+#    #+#             */
/*   Updated: 2025/07/13 21:44:15 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_path(char *cmd, char *envp[])
{
	char	**paths;
	char	*path;
	int		j;

	cmd = ft_strjoin("/", cmd);
	j = 0;
	while (envp[j] != NULL && ft_strncmp(envp[j], "PATH=", 5))
		j++;
	if (envp[j] == NULL)
		return (perror("Path does not exist"), free(cmd), NULL);
	paths = ft_split(&envp[j][5], ':');
	j = 0;
	while (paths[j] != NULL)
	{
		path = ft_strjoin(paths[j], cmd);
		if (access(path, F_OK) == 0)
			return (free_double_char(paths), free(cmd), path);
		free(path);
		j++;
	}
	ft_putstr_fd(&cmd[1], 2);
	ft_putstr_fd(": command not found\n", 2);
	return (free_double_char(paths), free(cmd), NULL);
}

void	child1(int *fd, char *argv[], char *envp[])
{
	int			infile;
	char		**cmd;
	char		*path;

	infile = open(argv[1], O_RDONLY);
	if (infile < 0)
	{
		perror(argv[1]);
		exit(EXIT_FAILURE);
	}
	cmd = ft_split(argv[2], ' ');
	path = find_path(cmd[0], envp);
	if (path == NULL)
	{
		close(infile);
		return (free_double_char(cmd), free(path));
	}
	dup2(infile, STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	close(infile);
	execve(path, cmd, envp);
	perror("execve failed");
	free_double_char(cmd);
	free(path);
	exit(EXIT_FAILURE);
}

void	child2(int *fd, char *argv[], char *envp[])
{
	int			outfile;
	char		**cmd;
	char		*path;

	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 00777);
	if (outfile < 0)
	{
		perror(argv[4]);
		exit(EXIT_FAILURE);
	}
	cmd = ft_split(argv[3], ' ');
	path = find_path(cmd[0], envp);
	if (path == NULL)
	{
		close(outfile);
		return (free_double_char(cmd), free(path));
	}
	dup2(fd[0], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	close(outfile);
	execve(path, cmd, envp);
	perror("execve failed");
	free_double_char(cmd);
	free(path);
	exit(EXIT_FAILURE);
}

/*int	main(int argc, char *argv[], char *envp[])
{
	int		fd[2];
	int		pid1;
	int		pid2;

	if (argc != 5)
		return (ft_putstr_fd("Invalid arguments!", 2), 1);
	if (pipe(fd) == -1)
		return (2);
	pid1 = fork();
	if (pid1 < 0)
		return (3);
	if (pid1 == 0)
		child1(fd, argv, envp);
	pid2 = fork();
	if (pid2 < 0)
		return (4);
	if (pid2 == 0)
		child2(fd, argv, envp);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}*/
