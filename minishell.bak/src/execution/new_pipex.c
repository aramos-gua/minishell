/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_pipex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtice <mtice@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 18:09:18 by mtice             #+#    #+#             */
/*   Updated: 2025/07/13 21:44:13 by mtice            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_double_char(char **arr)
{
	int	j;
	
	j = 0;
	while (arr[j] != NULL)
		free(arr[j++]);
	free(arr);
}

void	handle_error(char *message, char exit_status)
{
	if (errno != 0 && message != NULL)
		perror(message);
	else if (errno == 0 && message != NULL)
	{
		ft_putstr_fd("Error: ", 2);
		ft_putendl_fd(message, 2);
	}
	//free_all(info);
	if (exit_status == 'f')
		exit(EXIT_FAILURE);
	else if (exit_status == 's')
		exit(EXIT_SUCCESS);
}

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

/*void	exec(char *cmd, char *envp[])
{
	char **root_cmd;
	char *path;

	root_cmd = ft_split(cmd, ' ');
	path = find_path(root_cmd[0], envp);
	if (path == NULL)
	{
		ft_putstr_fd("Error with path!\n", 2);
		return ;
	}
	execve(path, root_cmd, envp);
	perror("execve failed");
	exit(EXIT_FAILURE);
}

void	ft_pipe(char *cmd, char *envp[])
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
	{
		ft_putstr_fd("Error with pipe!\n", 2);
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid < 0)
	{
		ft_putstr_fd("Error with pid!\n", 2);
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDIN_FILENO);
		close(fd[1]);
		exec(cmd, envp);
	}
	else {
		close(fd[0]);
		close(fd[1]);
		dup2(fd[0], STDOUT_FILENO);	
	}
}

int	main(int argc, char **argv, char **envp)
{
	int		fd_in;
	int		fd_out;
	int		j;

	if (argc < 5)
		return (ft_putendl_fd("Invalid arguments!", 2), 1);
	fd_in = open(argv[1], O_RDONLY);
	fd_out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 00777);
	if (fd_in < 0 || fd_out < 0)
	{
		ft_putstr_fd("Could not open file!\n", 2);
		exit(EXIT_FAILURE);
	}
	dup2(fd_in, STDIN_FILENO);
	j = 2;
	while (j < argc - 2)
		ft_pipe(argv[j++], envp);
	dup2(fd_out, STDOUT_FILENO);
	exec(argv[argc - 2], envp);
	return (0);
}*/

void	child_process(char *cmd, char **envp)
{
	char **cmds;
	char *path;

	cmds = ft_split(cmd, ' ');
	path = find_path(cmds[0], envp);
	if (path == NULL)
	{
		//free everything!
		exit(EXIT_FAILURE);
	}
	execve(path, cmds, envp);
	handle_error("execve failed", 'f');
	//free everything
}


void	exec_process(char *cmd, char **envp)
{
	int	fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		handle_error("Whats the message?", 'f');
	pid = fork();
	if (pid < 0)
		handle_error("Whats the message?", 'f');
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDIN_FILENO);
		child_process(cmd, envp);
	}
	else 
	{
		close(fd[1]);
		dup2(fd[0], STDOUT_FILENO);
	}
}

int main(int argc, char **argv, char **envp)
{
	int	fd_in;
	int	fd_out;
	int	i;

	i = 1;
	if (argc < 5)
		handle_error("Invalid arguments", 'f');
	if (!ft_strncmp(argv[1], "here_doc", 8))
		i++, printf("here_doc detected!"), exit(0);
	fd_in = open(argv[i], O_RDONLY);
	fd_out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 00777);
	if (fd_in < 0)
		handle_error(argv[i], 'f');
	if (fd_out < 0)
		handle_error(argv[argc - 1], 'f');
	dup2(fd_in, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_in);
	close(fd_out);
	while (i < argc - 2)
		exec_process(argv[++i], envp);
	exec_process(argv[i], envp);
	exit(0);
}
