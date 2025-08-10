/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Alejandro Ramos <alejandro.ramos.gua@gmai  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 19:05:11 by Alejandro Ram     #+#    #+#             */
/*   Updated: 2025/08/10 16:14:54 by Alejandro Ram    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//void	first_command(int i, t_data *all, int **pipes)
//{
////	int	devnull;
////
////	if (all->redirects->in_fd >= 0)
////		dup2(all->redirects->in_fd, STDIN_FILENO);
////	else
////	{
////		devnull = open("/dev/null", O_RDONLY);
////		dup2(devnull, STDIN_FILENO);
////		close(devnull);
////	}
//	dup2(pipes[i][1], STDOUT_FILENO);
//}
//
//void	last_command(t_data *all, int **pipes)
//{
//	if (all->redirects->out_fd >= 0)
//		dup2(all->redirects->out_fd, STDOUT_FILENO);
//	else
//	{
//		write(2, "minishell: Outfile Error\n", 25);
//		exit(1);
//	}
//}

char	*build_path(char *cmd, char **paths)
{
	int		i;
	char	*full_path;
	int		full_path_len;

	i = 0;
	while (paths[i])
	{
		full_path_len = ft_strlen(paths[i]) + ft_strlen(cmd) + 2;
		full_path = malloc(full_path_len);
		if (!full_path)
		{
			i++;
			continue ;
		}
		ft_strlcpy(full_path, paths[i], ft_strlen(paths[i]) + 1);
		ft_strlcat(full_path, "/", full_path_len);
		ft_strlcat(full_path, cmd, full_path_len);
		if (access(full_path, X_OK) == 0)
			return (free_split(paths), full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

char	*get_cmd_path(char *cmd, char **env)
{
	char	**paths;
	char	*path_env;
	char	*full_path;
	int		i;

	i = -1;
	path_env = NULL;
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		else
			return (NULL);
	}
	while (env[++i])
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			path_env = env[i] + 5;
	if (!path_env)
		return (NULL);
	paths = (ft_split(path_env, ':'));
	if (!paths)
		return (NULL);
	full_path = build_path(cmd, paths);
	if (!full_path)
		return (free_split(paths), NULL);
	if (access(full_path, X_OK) == 0)
		return (full_path);
	return (free_split(paths), NULL);
}

void	execute_command(t_data *all)
{
	char	*path;

	path = get_cmd_path(all->info.procs[0], all->c_envp);
	if (!path)
	{
		perror("execve");
		exit(1);
	}
	ft_printf("%s\n", path);
	ft_printf("execute_command\n");
	if (execve(path, all->info.procs, all->c_envp) == -1)
	{
		perror("execve");
		free(path);
		free_split(all->info.procs);
		exit (1);
	}
	free(path);
	free_split(all->info.procs);
}
